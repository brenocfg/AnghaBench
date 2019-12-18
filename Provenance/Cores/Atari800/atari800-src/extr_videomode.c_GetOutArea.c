#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t VIDEOMODE_MODE_t ;
struct TYPE_2__ {unsigned int param2src_w_mult; unsigned int src_width; unsigned int (* src2out_w_func ) (unsigned int) ;unsigned int src_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  Atari800_TV_NTSC ; 
 int /*<<< orphan*/  Atari800_tv_mode ; 
#define  VIDEOMODE_HORIZONTAL_FULL 133 
#define  VIDEOMODE_HORIZONTAL_NARROW 132 
#define  VIDEOMODE_HORIZONTAL_TV 131 
 unsigned int VIDEOMODE_MAX_HORIZONTAL_AREA ; 
 unsigned int VIDEOMODE_MAX_VERTICAL_AREA ; 
#define  VIDEOMODE_VERTICAL_FULL 130 
#define  VIDEOMODE_VERTICAL_SHORT 129 
#define  VIDEOMODE_VERTICAL_TV 128 
 unsigned int VIDEOMODE_custom_horizontal_area ; 
 unsigned int VIDEOMODE_custom_vertical_area ; 
 int VIDEOMODE_horizontal_area ; 
 int VIDEOMODE_vertical_area ; 
 TYPE_1__* display_modes ; 
 unsigned int stub1 (unsigned int) ; 

__attribute__((used)) static void GetOutArea(unsigned int *w, unsigned int *h, VIDEOMODE_MODE_t display_mode)
{
	switch (VIDEOMODE_horizontal_area) {
	case VIDEOMODE_HORIZONTAL_NARROW:
		VIDEOMODE_custom_horizontal_area = 320;
		break;
	case VIDEOMODE_HORIZONTAL_TV:
		VIDEOMODE_custom_horizontal_area = 336;
		break;
	case VIDEOMODE_HORIZONTAL_FULL:
		VIDEOMODE_custom_horizontal_area = VIDEOMODE_MAX_HORIZONTAL_AREA;
		break;
	}
	*w = VIDEOMODE_custom_horizontal_area * display_modes[display_mode].param2src_w_mult;
	if (*w > display_modes[display_mode].src_width)
		*w = display_modes[display_mode].src_width;
	*w = (*display_modes[display_mode].src2out_w_func)(*w);

	switch (VIDEOMODE_vertical_area) {
	case VIDEOMODE_VERTICAL_SHORT:
		VIDEOMODE_custom_vertical_area = 200;
		break;
	case VIDEOMODE_VERTICAL_TV:
		if (Atari800_tv_mode == Atari800_TV_NTSC)
			VIDEOMODE_custom_vertical_area = 224;
		else
			VIDEOMODE_custom_vertical_area = 240;
		break;
	case VIDEOMODE_VERTICAL_FULL:
		VIDEOMODE_custom_vertical_area = VIDEOMODE_MAX_VERTICAL_AREA;
		break;
	}
	*h = VIDEOMODE_custom_vertical_area;
	if (*h > display_modes[display_mode].src_height)
		*h = display_modes[display_mode].src_height;
}