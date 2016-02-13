#include <iostream>


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>


#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <intraface\FaceAlignment.h>
#include <intraface\XXDescriptor.h>

using namespace std;
using namespace cv;



bool compareRect(cv::Rect r1, cv::Rect r2) { return r1.height < r2.height; }

void drawPose(cv::Mat& img, const cv::Mat& rot, float lineL)
{
	int loc[2] = { 70, 70 };
	int thickness = 2;
	int lineType = 8;

	cv::Mat P = (cv::Mat_<float>(3, 4) <<
		0, lineL, 0, 0,
		0, 0, -lineL, 0,
		0, 0, 0, -lineL);
	P = rot.rowRange(0, 2)*P;
	P.row(0) += loc[0];
	P.row(1) += loc[1];
	cv::Point p0(P.at<float>(0, 0), P.at<float>(1, 0));

	line(img, p0, cv::Point(P.at<float>(0, 1), P.at<float>(1, 1)), cv::Scalar(255, 0, 0), thickness, lineType);
	line(img, p0, cv::Point(P.at<float>(0, 2), P.at<float>(1, 2)), cv::Scalar(0, 255, 0), thickness, lineType);
	line(img, p0, cv::Point(P.at<float>(0, 3), P.at<float>(1, 3)), cv::Scalar(0, 0, 255), thickness, lineType);
}

void cosasLocas(Mat cuadro)
{
	cout << "Cosas locas a la orden se�or!!" << endl;
	imshow("Main", cuadro);
}




int main()
{
	cout << "Intentar haceer funcionar INTRAFACE" << endl;

	char detectionModel[] = "../models/DetectionModel-v1.5.bin";
	char trackingModel[] = "../models/TrackingModel-v1.10.bin";
	string faceDetectionModel("../models/haarcascade_frontalface_alt2.xml");



	INTRAFACE::XXDescriptor xxd(4);
	INTRAFACE::FaceAlignment fa(detectionModel, trackingModel, &xxd);

	if (!fa.Initialized())
	{
		cerr << "FaceAligment cannot be initialized" << endl;
		return -1;
	}

	cv::CascadeClassifier face_cascade;
	if (!face_cascade.load(faceDetectionModel))
	{
		cerr << "Error loading face detection model" << endl;
		return -1;
	}
	
	VideoCapture capture;

	int key = 0;
	bool isDetect = true;
	float score, notFace = 0.3;
	Mat X, X0;
	string winname = ("Demo Intraface Tracker");
	capture.open(0);
	Mat frame;
	
	
	if (capture.isOpened())
	{
		while (true)
		{
			Mat frame;
			Mat frameOrig;
			capture.read(frame);
			Mat gray_frame;
			cvtColor(frame, gray_frame, COLOR_BGR2GRAY);


			if (gray_frame.rows == 0 || gray_frame.cols == 0)
			{
				cout << "Error: No frame!!" << endl;
				break;
			}
			else
			{
				cout << "Llamando a cosas locas xD" << endl;
				cosasLocas(gray_frame);
			}
			
			
			if (waitKey(27) >= 0)
			{
				break;
			}
			
		}
	}
	cvDestroyAllWindows();
	capture.release();
	cin.get();
	return 0;
}

