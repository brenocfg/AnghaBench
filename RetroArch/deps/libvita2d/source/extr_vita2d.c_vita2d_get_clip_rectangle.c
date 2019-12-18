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

/* Variables and functions */
 int clip_rect_x_max ; 
 int clip_rect_x_min ; 
 int clip_rect_y_max ; 
 int clip_rect_y_min ; 

void vita2d_get_clip_rectangle(int *x_min, int *y_min, int *x_max, int *y_max)
{
	*x_min = clip_rect_x_min;
	*y_min = clip_rect_y_min;
	*x_max = clip_rect_x_max;
	*y_max = clip_rect_y_max;
}