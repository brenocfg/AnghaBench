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

__attribute__((used)) static void ir_convert_to_vres(float* x, float* y, enum aspect_t aspect, unsigned int vx, unsigned int vy) {
	int xs, ys;

	if (aspect == WIIUSE_ASPECT_16_9) {
		xs = WM_ASPECT_16_9_X;
		ys = WM_ASPECT_16_9_Y;
	} else {
		xs = WM_ASPECT_4_3_X;
		ys = WM_ASPECT_4_3_Y;
	}

	*x -= ((1024-xs)/2);
	*y -= ((768-ys)/2);

	*x = (*x / (float)xs) * vx;
	*y = (*y / (float)ys) * vy;
}