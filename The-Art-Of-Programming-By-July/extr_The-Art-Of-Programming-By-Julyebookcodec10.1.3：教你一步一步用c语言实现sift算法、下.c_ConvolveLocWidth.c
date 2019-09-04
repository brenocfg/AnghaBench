#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fl; } ;
struct TYPE_5__ {int cols; int step; TYPE_1__ data; } ;
typedef  TYPE_2__ CvMat ;

/* Variables and functions */

float ConvolveLocWidth(float* kernel, int dim, CvMat * src, int x, int y)   
{  
#define Src(ROW,COL) ((float *)(src->data.fl + src->step/sizeof(float) *(ROW)))[(COL)]  
	unsigned int i;  
	float pixel = 0;  
	int col;  
	int cen = dim / 2;  
	//printf("ConvolveLoc(): Applying convoluation at location (%d, %d)/n", x, y);  
	for ( i = 0; i < dim; i++)   
	{  
		col = x + (i - cen);  
		if (col < 0)  
			col = 0;  
		if (col >= src->cols)  
			col = src->cols - 1;  
		pixel += kernel[i] * Src(y,col);  
	}  
	if (pixel > 1)  
		pixel = 1;  
	return pixel;  
}