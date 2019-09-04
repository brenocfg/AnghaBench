#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fl; } ;
struct TYPE_7__ {int cols; int rows; int step; TYPE_1__ data; } ;
typedef  TYPE_2__ CvMat ;

/* Variables and functions */
 int /*<<< orphan*/  CV_32FC1 ; 
 TYPE_2__* cvCreateMat (int,int,int /*<<< orphan*/ ) ; 

CvMat * halfSizeImage(CvMat * im)   
{  
	unsigned int i,j;  
	int w = im->cols/2;  
	int h = im->rows/2;   
	CvMat *imnew = cvCreateMat(h, w, CV_32FC1);  

#define Im(ROW,COL) ((float *)(im->data.fl + im->step/sizeof(float) *(ROW)))[(COL)]  
#define Imnew(ROW,COL) ((float *)(imnew->data.fl + imnew->step/sizeof(float) *(ROW)))[(COL)]  
	for ( j = 0; j < h; j++)   
		for ( i = 0; i < w; i++)   
			Imnew(j,i)=Im(j*2, i*2);  
	return imnew;  
}