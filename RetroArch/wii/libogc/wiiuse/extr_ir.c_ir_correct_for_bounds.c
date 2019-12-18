#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum aspect_t { ____Placeholder_aspect_t } aspect_t ;

/* Variables and functions */
 int WIIUSE_ASPECT_16_9 ; 
 int WM_ASPECT_16_9_X ; 
 int WM_ASPECT_16_9_Y ; 
 int WM_ASPECT_4_3_X ; 
 int WM_ASPECT_4_3_Y ; 

__attribute__((used)) static int ir_correct_for_bounds(float* x, float* y, enum aspect_t aspect, int offset_x, int offset_y) {
	float x0, y0;
	int xs, ys;

	if (aspect == WIIUSE_ASPECT_16_9) {
		xs = WM_ASPECT_16_9_X;
		ys = WM_ASPECT_16_9_Y;
	} else {
		xs = WM_ASPECT_4_3_X;
		ys = WM_ASPECT_4_3_Y;
	}

	x0 = ((1024 - xs) / 2) + offset_x;
	y0 = ((768 - ys) / 2) + offset_y;

	if ((*x >= x0)
		&& (*x <= (x0 + xs))
		&& (*y >= y0)
		&& (*y <= (y0 + ys)))
	{
		*x -= offset_x;
		*y -= offset_y;

		return 1;
	}

	return 0;
}