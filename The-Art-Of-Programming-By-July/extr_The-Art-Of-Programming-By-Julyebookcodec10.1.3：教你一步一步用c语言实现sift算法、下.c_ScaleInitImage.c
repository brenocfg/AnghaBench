#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cols; int /*<<< orphan*/  rows; } ;
typedef  TYPE_1__ CvMat ;

/* Variables and functions */
 int /*<<< orphan*/  BlurImage (TYPE_1__*,TYPE_1__*,double) ; 
 int /*<<< orphan*/  CV_32FC1 ; 
 scalar_t__ DOUBLE_BASE_IMAGE_SIZE ; 
 int INITSIGMA ; 
 TYPE_1__* cvCreateMat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvReleaseMat (TYPE_1__**) ; 
 TYPE_1__* doubleSizeImage2 (TYPE_1__*) ; 
 double sqrt (int) ; 

CvMat *ScaleInitImage(CvMat * im)   
{  
	double sigma,preblur_sigma;  
	CvMat *imMat;  
	CvMat * dst;  
	CvMat *tempMat;  
	//首先对图像进行平滑滤波，抑制噪声  
	imMat = cvCreateMat(im->rows, im->cols, CV_32FC1);  
	BlurImage(im, imMat, INITSIGMA);  
	//针对两种情况分别进行处理：初始化放大原始图像或者在原图像基础上进行后续操作  
	//建立金字塔的最底层  
	if (DOUBLE_BASE_IMAGE_SIZE)   
	{  
		tempMat = doubleSizeImage2(imMat);//对扩大两倍的图像进行二次采样，采样率为0.5，采用线性插值  
#define TEMPMAT(ROW,COL) ((float *)(tempMat->data.fl + tempMat->step/sizeof(float) * (ROW)))[(COL)]  

		dst = cvCreateMat(tempMat->rows, tempMat->cols, CV_32FC1);  
		preblur_sigma = 1.0;//sqrt(2 - 4*INITSIGMA*INITSIGMA);  
		BlurImage(tempMat, dst, preblur_sigma);   

		// The initial blurring for the first image of the first octave of the pyramid.  
		sigma = sqrt( (4*INITSIGMA*INITSIGMA) + preblur_sigma * preblur_sigma );  
		//  sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4);  
		//printf("Init Sigma: %f/n", sigma);  
		BlurImage(dst, tempMat, sigma);       //得到金字塔的最底层-放大2倍的图像  
		cvReleaseMat( &dst );   
		return tempMat;  
	}   
	else   
	{  
		dst = cvCreateMat(im->rows, im->cols, CV_32FC1);  
		//sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA);  
		preblur_sigma = 1.0;//sqrt(2 - 4*INITSIGMA*INITSIGMA);  
		sigma = sqrt( (4*INITSIGMA*INITSIGMA) + preblur_sigma * preblur_sigma );  
		//printf("Init Sigma: %f/n", sigma);  
		BlurImage(imMat, dst, sigma);        //得到金字塔的最底层：原始图像大小  
		return dst;  
	}   
}