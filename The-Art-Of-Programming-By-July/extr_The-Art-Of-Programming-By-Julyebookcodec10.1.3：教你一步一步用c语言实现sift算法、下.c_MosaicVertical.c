#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ fl; } ;
struct TYPE_9__ {int rows; int cols; int step; TYPE_1__ data; } ;
typedef  TYPE_2__ CvMat ;

/* Variables and functions */
 int /*<<< orphan*/  CV_32FC1 ; 
 TYPE_2__* cvCreateMat (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvZero (TYPE_2__*) ; 
 int /*<<< orphan*/  max (int,int) ; 

CvMat* MosaicVertical( CvMat* im1, CvMat* im2 )  
{  
	int row,col;  
	CvMat *mosaic = cvCreateMat(im1->rows+im2->rows,max(im1->cols,im2->cols), CV_32FC1);  
#define Mosaic(ROW,COL) ((float*)(mosaic->data.fl + mosaic->step/sizeof(float)*(ROW)))[(COL)]  
#define Im11Mat(ROW,COL) ((float *)(im1->data.fl + im1->step/sizeof(float) *(ROW)))[(COL)]  
#define Im22Mat(ROW,COL) ((float *)(im2->data.fl + im2->step/sizeof(float) *(ROW)))[(COL)]  
	cvZero(mosaic);  

	/* Copy images into mosaic1. */  
	for ( row = 0; row < im1->rows; row++)  
		for ( col = 0; col < im1->cols; col++)  
			Mosaic(row,col)= Im11Mat(row,col) ;  
	for ( row = 0; row < im2->rows; row++)  
		for ( col = 0; col < im2->cols; col++)  
			Mosaic((row+im1->rows),col)=Im22Mat(row,col) ;  

	return mosaic;  
}