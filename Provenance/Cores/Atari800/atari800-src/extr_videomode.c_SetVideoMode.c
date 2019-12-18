#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; } ;
typedef  TYPE_1__ VIDEOMODE_resolution_t ;
typedef  size_t VIDEOMODE_MODE_t ;
struct TYPE_7__ {int (* out2src_w_func ) (unsigned int) ;int src_width; int src_height; int param2src_w_mult; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_SetVideoMode (TYPE_1__*,int,size_t,int) ; 
 int /*<<< orphan*/  RotateResolution (TYPE_1__*) ; 
 int /*<<< orphan*/  SetScreenVisible () ; 
 int VIDEOMODE_MAX_HORIZONTAL_AREA ; 
 int VIDEOMODE_MAX_VERTICAL_AREA ; 
 size_t VIDEOMODE_MODE_LASTWITHHUD ; 
 unsigned int VIDEOMODE_actual_width ; 
 int VIDEOMODE_dest_height ; 
 int VIDEOMODE_dest_offset_left ; 
 int VIDEOMODE_dest_offset_top ; 
 int VIDEOMODE_dest_width ; 
 int VIDEOMODE_horizontal_offset ; 
 int VIDEOMODE_src_height ; 
 int VIDEOMODE_src_offset_left ; 
 int VIDEOMODE_src_offset_top ; 
 int VIDEOMODE_src_width ; 
 int VIDEOMODE_vertical_offset ; 
 TYPE_2__* display_modes ; 
 int stub1 (unsigned int) ; 

__attribute__((used)) static void SetVideoMode(VIDEOMODE_resolution_t *res, VIDEOMODE_MODE_t display_mode,
                         unsigned int out_w, unsigned int out_h,
                         int windowed, int rotate)
{
	VIDEOMODE_actual_width = out_w;
	VIDEOMODE_src_width = (*display_modes[display_mode].out2src_w_func)(out_w);
	VIDEOMODE_src_height = out_h;
	VIDEOMODE_src_offset_left = (display_modes[display_mode].src_width - VIDEOMODE_src_width) / 2;
	VIDEOMODE_src_offset_top = (display_modes[display_mode].src_height - VIDEOMODE_src_height) / 2;

	if (VIDEOMODE_horizontal_offset < -VIDEOMODE_MAX_HORIZONTAL_AREA)
		VIDEOMODE_horizontal_offset = -VIDEOMODE_MAX_HORIZONTAL_AREA;
	else if (VIDEOMODE_horizontal_offset > VIDEOMODE_MAX_HORIZONTAL_AREA)
		VIDEOMODE_horizontal_offset = VIDEOMODE_MAX_HORIZONTAL_AREA;
	if (VIDEOMODE_vertical_offset < -VIDEOMODE_MAX_VERTICAL_AREA)
		VIDEOMODE_vertical_offset = -VIDEOMODE_MAX_VERTICAL_AREA;
	else if (VIDEOMODE_vertical_offset > VIDEOMODE_MAX_VERTICAL_AREA)
		VIDEOMODE_vertical_offset = VIDEOMODE_MAX_VERTICAL_AREA;
	{
		int x = VIDEOMODE_horizontal_offset * display_modes[display_mode].param2src_w_mult;
		int y = VIDEOMODE_vertical_offset;
		if (x < -(int)VIDEOMODE_src_offset_left)
			x = -(int)VIDEOMODE_src_offset_left;
		else if (x > (int)(display_modes[display_mode].src_width - VIDEOMODE_src_offset_left - VIDEOMODE_src_width))
			x = (int)display_modes[display_mode].src_width - VIDEOMODE_src_offset_left - VIDEOMODE_src_width;
		if (y < -(int)VIDEOMODE_src_offset_top)
			y = -(int)VIDEOMODE_src_offset_top;
		else if (y > (int)(display_modes[display_mode].src_height - VIDEOMODE_src_offset_top - VIDEOMODE_src_height))
			y = (int)display_modes[display_mode].src_height - VIDEOMODE_src_offset_top - VIDEOMODE_src_height;
		VIDEOMODE_src_offset_left += x;
		VIDEOMODE_src_offset_top += y;
	}
	if (rotate) {
		unsigned int tmp = VIDEOMODE_dest_width;
		VIDEOMODE_dest_width = VIDEOMODE_dest_height;
		VIDEOMODE_dest_height = tmp;
		RotateResolution(res);
	}
	VIDEOMODE_dest_offset_left = (res->width - VIDEOMODE_dest_width) / 2;
	VIDEOMODE_dest_offset_top = (res->height - VIDEOMODE_dest_height) / 2;
	if (display_mode <= VIDEOMODE_MODE_LASTWITHHUD)
		SetScreenVisible();
	PLATFORM_SetVideoMode(res, windowed, display_mode, rotate);
}