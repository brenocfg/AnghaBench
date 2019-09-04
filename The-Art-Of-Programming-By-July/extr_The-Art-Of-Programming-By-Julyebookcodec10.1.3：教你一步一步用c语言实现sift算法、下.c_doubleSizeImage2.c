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

CvMat * doubleSizeImage2(CvMat * im)   
{  
	unsigned int i,j;  
	int w = im->cols*2;  
	int h = im->rows*2;   
	CvMat *imnew = cvCreateMat(h, w, CV_32FC1);  

#define Im(ROW,COL) ((float *)(im->data.fl + im->step/sizeof(float) *(ROW)))[(COL)]  
#define Imnew(ROW,COL) ((float *)(imnew->data.fl + imnew->step/sizeof(float) *(ROW)))[(COL)]  

	// fill every pixel so we don't have to worry about skipping pixels later  
	for ( j = 0; j < h; j++)   
	{  
		for ( i = 0; i < w; i++)   
		{  
			Imnew(j,i)=Im(j/2, i/2);  
		}  
	}  
	/* 
	A B C 
	E F G 
	H I J 
	pixels A C H J are pixels from original image 
	pixels B E G I F are interpolated pixels 
	*/  
	// interpolate pixels B and I  
	for ( j = 0; j < h; j += 2)  
		for ( i = 1; i < w - 1; i += 2)  
			Imnew(j,i)=0.5*(Im(j/2, i/2)+Im(j/2, i/2+1));  
	// interpolate pixels E and G  
	for ( j = 1; j < h - 1; j += 2)  
		for ( i = 0; i < w; i += 2)  
			Imnew(j,i)=0.5*(Im(j/2, i/2)+Im(j/2+1, i/2));  
	// interpolate pixel F  
	for ( j = 1; j < h - 1; j += 2)  
		for ( i = 1; i < w - 1; i += 2)  
			Imnew(j,i)=0.25*(Im(j/2, i/2)+Im(j/2+1, i/2)+Im(j/2, i/2+1)+Im(j/2+1, i/2+1));  
	return imnew;  
}