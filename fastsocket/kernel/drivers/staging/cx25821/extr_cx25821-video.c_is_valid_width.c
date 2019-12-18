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
typedef  scalar_t__ v4l2_std_id ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ V4L2_STD_NTSC_M ; 
 scalar_t__ V4L2_STD_PAL_BG ; 

int is_valid_width(u32 width, v4l2_std_id tvnorm)
{
	if (tvnorm == V4L2_STD_PAL_BG) {
		if (width == 352 || width == 720)
			return 1;
		else
			return 0;
	}

	if (tvnorm == V4L2_STD_NTSC_M) {
		if (width == 320 || width == 352 || width == 720)
			return 1;
		else
			return 0;
	}
	return 0;
}