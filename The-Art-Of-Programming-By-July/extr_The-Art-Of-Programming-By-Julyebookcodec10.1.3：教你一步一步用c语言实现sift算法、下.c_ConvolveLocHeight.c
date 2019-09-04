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
struct TYPE_5__ {int rows; int step; TYPE_1__ data; } ;
typedef  TYPE_2__ CvMat ;

/* Variables and functions */

float ConvolveLocHeight(float* kernel, int dim, CvMat * src, int x, int y)   
{  
#define Src(ROW,COL) ((float *)(src->data.fl + src->step/sizeof(float) *(ROW)))[(COL)]  
	unsigned int j;  
	float pixel = 0;  
	int cen = dim / 2;  
	//printf("ConvolveLoc(): Applying convoluation at location (%d, %d)/n", x, y);  
	for ( j = 0; j < dim; j++)   
	{  
		int row = y + (j - cen);  
		if (row < 0)  
			row = 0;  
		if (row >= src->rows)  
			row = src->rows - 1;  
		pixel += kernel[j] * Src(row,x);  
	}  
	if (pixel > 1)  
		pixel = 1;  
	return pixel;  
}