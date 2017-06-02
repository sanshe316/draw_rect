#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

int main() {
    cv::Mat image = cv::imread("image.jpg");
    std::vector<std::string> label {"class1", "class2", "class3"};
    //std::vector<std::vector<float> > rect(3, std::vector<float>(6,0));
    std::vector<std::vector<float> > rect { // x1, y1, x2, y2, prob, class_id
        { 906.467407, 1307.500610, 1406.386108, 1880.144897, 0.999915, 0.000000 },
        { 508.087006, 1125.142334,  953.199829, 1649.642334, 0.999696, 0.000000 },
        { 467.721466, 2523.903076,  703.601135, 2796.344482, 0.866193, 1.000000 } };
    int lineType = CV_AA; // change it to 8 to see non-antialiased graphics
    char wndname[] = "Drawing Demo";
    int thickness = 10;
    int fontFace = 0;
    double fontScale = 5;
    std::vector<int> imwrite_params;
    imwrite_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    imwrite_params.push_back(75);
    for (int i = 0; i < rect.size(); i++) {
        cv::Point pt1, pt2;
        pt1.x = rect[i][0];
        pt1.y = rect[i][1];
        pt2.x = rect[i][2];
        pt2.y = rect[i][3];
        cv::rectangle(image, pt1, pt2, cv::Scalar(0,255,0), thickness, lineType);
        //std::string text = label[(int)rect[i][5]] + " (" + std::to_string(rect[i][4]) + ")";
        std::ostringstream prob;
        //prob << std::setprecision(2) << rect[i][4];
        prob << std::fixed << std::setprecision(2) << rect[i][4];
        std::cout << prob.str() << std::endl;
        std::string text = label[(int)rect[i][5]] + " (" + prob.str() + ")";
        putText(image, text, pt1, fontFace, fontScale, cv::Scalar(0,0,255), thickness, lineType);
    }
        cv::imwrite("img_detection.jpg", image, imwrite_params);
        cv::namedWindow(wndname, CV_WINDOW_NORMAL);
        cv::resizeWindow(wndname, 300, 300);
        imshow(wndname, image);
        cv::waitKey();
        return 0;
}
