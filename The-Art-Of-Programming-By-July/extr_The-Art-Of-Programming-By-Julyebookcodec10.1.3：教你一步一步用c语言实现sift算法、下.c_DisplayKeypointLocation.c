#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int col; int row; struct TYPE_3__* next; } ;
typedef  TYPE_1__* Keypoint ;
typedef  int /*<<< orphan*/  IplImage ;
typedef  int /*<<< orphan*/  ImageOctaves ;

/* Variables and functions */
 int /*<<< orphan*/  CV_RGB (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvPoint (int,int) ; 
 TYPE_1__* keypoints ; 

void DisplayKeypointLocation(IplImage* image, ImageOctaves *GaussianPyr)  
{  

	Keypoint p = keypoints; // p指向第一个结点  
	while(p) // 没到表尾  
	{     
		cvLine( image, cvPoint((int)((p->col)-3),(int)(p->row)),   
			cvPoint((int)((p->col)+3),(int)(p->row)), CV_RGB(255,255,0),  
			1, 8, 0 );  
		cvLine( image, cvPoint((int)(p->col),(int)((p->row)-3)),   
			cvPoint((int)(p->col),(int)((p->row)+3)), CV_RGB(255,255,0),  
			1, 8, 0 );  
		//  cvCircle(image,cvPoint((uchar)(p->col),(uchar)(p->row)),  
		//   (int)((GaussianPyr[p->octave].Octave)[p->level].absolute_sigma),  
		//   CV_RGB(255,0,0),1,8,0);  
		p=p->next;  
	}   
}