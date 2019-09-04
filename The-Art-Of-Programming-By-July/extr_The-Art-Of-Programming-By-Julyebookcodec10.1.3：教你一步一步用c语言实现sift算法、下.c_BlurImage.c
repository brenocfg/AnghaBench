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
 int /*<<< orphan*/  CV_32FC1 ; 
 int /*<<< orphan*/  Convolve1DHeight (float*,int,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Convolve1DWidth (float*,int,TYPE_1__*,TYPE_1__*) ; 
 double GAUSSKERN ; 
 float* GaussianKernel1D (float,int) ; 
 TYPE_1__* cvCreateMat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvReleaseMat (TYPE_1__**) ; 
 scalar_t__ max (float,double) ; 

int BlurImage(CvMat * src, CvMat * dst, float sigma)   
{  
	float* convkernel;  
	int dim = (int) max(3.0f, 2.0 * GAUSSKERN * sigma + 1.0f);  
	CvMat *tempMat;  
	// make dim odd  
	if (dim % 2 == 0)  
		dim++;  
	tempMat = cvCreateMat(src->rows, src->cols, CV_32FC1);  
	convkernel = GaussianKernel1D(sigma, dim);  

	Convolve1DWidth(convkernel, dim, src, tempMat);  
	Convolve1DHeight(convkernel, dim, tempMat, dst);  
	cvReleaseMat(&tempMat);  
	return dim;  
}