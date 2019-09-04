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
struct TYPE_5__ {int cols; int rows; int step; TYPE_1__ data; } ;
typedef  TYPE_2__ CvMat ;

/* Variables and functions */

float getPixelBI(CvMat * im, float col, float row)   
{  
	int irow, icol;  
	float rfrac, cfrac;  
	float row1 = 0, row2 = 0;  
	int width=im->cols;  
	int height=im->rows;  
#define ImMat(ROW,COL) ((float *)(im->data.fl + im->step/sizeof(float) *(ROW)))[(COL)]  

	irow = (int) row;  
	icol = (int) col;  

	if (irow < 0 || irow >= height  
		|| icol < 0 || icol >= width)  
		return 0;  
	if (row > height - 1)  
		row = height - 1;  
	if (col > width - 1)  
		col = width - 1;  
	rfrac = 1.0 - (row - (float) irow);  
	cfrac = 1.0 - (col - (float) icol);  
	if (cfrac < 1)   
	{  
		row1 = cfrac * ImMat(irow,icol) + (1.0 - cfrac) * ImMat(irow,icol+1);  
	}   
	else   
	{  
		row1 = ImMat(irow,icol);  
	}  
	if (rfrac < 1)   
	{  
		if (cfrac < 1)   
		{  
			row2 = cfrac * ImMat(irow+1,icol) + (1.0 - cfrac) * ImMat(irow+1,icol+1);  
		} else   
		{  
			row2 = ImMat(irow+1,icol);  
		}  
	}  
	return rfrac * row1 + (1.0 - rfrac) * row2;  
}