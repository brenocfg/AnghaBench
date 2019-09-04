#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* Octave; } ;
struct TYPE_7__ {size_t octave; size_t level; float col; float row; struct TYPE_7__* next; int /*<<< orphan*/  ori; } ;
struct TYPE_6__ {float absolute_sigma; } ;
typedef  TYPE_2__* Keypoint ;
typedef  int /*<<< orphan*/  IplImage ;
typedef  TYPE_3__ ImageOctaves ;

/* Variables and functions */
 int /*<<< orphan*/  CV_RGB (int,int,int /*<<< orphan*/ ) ; 
 float cos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvPoint (int,int) ; 
 TYPE_2__* keyDescriptors ; 
 float sin (int /*<<< orphan*/ ) ; 

void DisplayOrientation (IplImage* image, ImageOctaves *GaussianPyr)  
{  
	Keypoint p = keyDescriptors; // p指向第一个结点  
	while(p) // 没到表尾  
	{  
		float scale=(GaussianPyr[p->octave].Octave)[p->level].absolute_sigma;  
		float autoscale = 3.0;   
		float uu=autoscale*scale*cos(p->ori);  
		float vv=autoscale*scale*sin(p->ori);  
		float x=(p->col)+uu;  
		float y=(p->row)+vv;  
		cvLine( image, cvPoint((int)(p->col),(int)(p->row)),   
			cvPoint((int)x,(int)y), CV_RGB(255,255,0),  
			1, 8, 0 );  
		// Arrow head parameters  
		float alpha = 0.33; // Size of arrow head relative to the length of the vector  
		float beta = 0.33;  // Width of the base of the arrow head relative to the length  

		float xx0= (p->col)+uu-alpha*(uu+beta*vv);  
		float yy0= (p->row)+vv-alpha*(vv-beta*uu);  
		float xx1= (p->col)+uu-alpha*(uu-beta*vv);  
		float yy1= (p->row)+vv-alpha*(vv+beta*uu);  
		cvLine( image, cvPoint((int)xx0,(int)yy0),   
			cvPoint((int)x,(int)y), CV_RGB(255,255,0),  
			1, 8, 0 );  
		cvLine( image, cvPoint((int)xx1,(int)yy1),   
			cvPoint((int)x,(int)y), CV_RGB(255,255,0),  
			1, 8, 0 );  
		p=p->next;  
	}   
}