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
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_1__ VIDEOMODE_resolution_t ;

/* Variables and functions */
 scalar_t__ VIDEOMODE_dest_height ; 
 scalar_t__ VIDEOMODE_dest_width ; 

__attribute__((used)) static void CropVideoArea(VIDEOMODE_resolution_t const *screen_res, unsigned int *out_w, unsigned int *out_h, double mult_w, double mult_h)
{
	if (VIDEOMODE_dest_width > screen_res->width) {
		VIDEOMODE_dest_width = screen_res->width;
		*out_w = (double)VIDEOMODE_dest_width / mult_w;
	}
	if (VIDEOMODE_dest_height > screen_res->height) {
		VIDEOMODE_dest_height = screen_res->height;
		*out_h = (double)VIDEOMODE_dest_height / mult_h;
	}
}