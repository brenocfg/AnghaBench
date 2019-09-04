#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fl; } ;
struct TYPE_6__ {int step; TYPE_1__ data; } ;
typedef  TYPE_2__ CvMat ;

/* Variables and functions */
 int /*<<< orphan*/  CV_32FC1 ; 
 double CV_PI ; 
 double GAUSSKERN ; 
 TYPE_2__* cvCreateMat (int,int,int /*<<< orphan*/ ) ; 
 float exp (double) ; 
 scalar_t__ max (float,double) ; 
 float sqrt (double) ; 

CvMat* GaussianKernel2D(float sigma)   
{  
	// int dim = (int) max(3.0f, GAUSSKERN * sigma);  
	int dim = (int) max(3.0f, 2.0 * GAUSSKERN *sigma + 1.0f);  
	// make dim odd  
	if (dim % 2 == 0)  
		dim++;  
	//printf("GaussianKernel(): Creating %dx%d matrix for sigma=%.3f gaussian/n", dim, dim, sigma);  
	CvMat* mat=cvCreateMat(dim, dim, CV_32FC1);  
#define Mat(ROW,COL) ((float *)(mat->data.fl + mat->step/sizeof(float) *(ROW)))[(COL)]  
	float s2 = sigma * sigma;  
	int c = dim / 2;  
	//printf("%d %d/n", mat.size(), mat[0].size());  
	float m= 1.0/(sqrt(2.0 * CV_PI) * sigma);  
	for (int i = 0; i < (dim + 1) / 2; i++)   
	{  
		for (int j = 0; j < (dim + 1) / 2; j++)   
		{  
			//printf("%d %d %d/n", c, i, j);  
			float v = m * exp(-(1.0*i*i + 1.0*j*j) / (2.0 * s2));  
			Mat(c+i,c+j) =v;  
			Mat(c-i,c+j) =v;  
			Mat(c+i,c-j) =v;  
			Mat(c-i,c-j) =v;  
		}  
	}  
	// normalizeMat(mat);  
	return mat;  
}