#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omapfb_update_window {int x; int y; int width; int height; int out_x; int out_y; int out_width; int out_height; int format; } ;
struct list_head {int dummy; } ;
struct blizzard_request {int dummy; } ;
struct TYPE_4__ {int max_transmit_size; TYPE_1__* plane; } ;
struct TYPE_3__ {int bpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PREQ (int,unsigned int,int,unsigned int,int,unsigned int,int,unsigned int) ; 
#define  OMAPFB_COLOR_YUV420 128 
 int OMAPFB_FORMAT_FLAG_TEARSYNC ; 
 int OMAPFB_FORMAT_MASK ; 
 TYPE_2__ blizzard ; 

__attribute__((used)) static void create_req_list(int plane_idx,
			    struct omapfb_update_window *win,
			    struct list_head *req_head)
{
	struct blizzard_request *req;
	int x = win->x;
	int y = win->y;
	int width = win->width;
	int height = win->height;
	int x_out = win->out_x;
	int y_out = win->out_y;
	int width_out = win->out_width;
	int height_out = win->out_height;
	int color_mode;
	int bpp;
	int flags;
	unsigned int ystart = y;
	unsigned int yspan = height;
	unsigned int ystart_out = y_out;
	unsigned int yspan_out = height_out;

	flags = win->format & ~OMAPFB_FORMAT_MASK;
	color_mode = win->format & OMAPFB_FORMAT_MASK;
	switch (color_mode) {
	case OMAPFB_COLOR_YUV420:
		/* Embedded window with different color mode */
		bpp = 12;
		/* X, Y, height must be aligned at 2, width at 4 pixels */
		x &= ~1;
		y &= ~1;
		height = yspan = height & ~1;
		width = width & ~3;
		break;
	default:
		/* Same as the plane color mode */
		bpp = blizzard.plane[plane_idx].bpp;
		break;
	}
	if (width * height * bpp / 8 > blizzard.max_transmit_size) {
		yspan = blizzard.max_transmit_size / (width * bpp / 8);
		yspan_out = yspan * height_out / height;
		ADD_PREQ(x, ystart, width, yspan, x_out, ystart_out,
			 width_out, yspan_out);
		ystart += yspan;
		ystart_out += yspan_out;
		yspan = height - yspan;
		yspan_out = height_out - yspan_out;
		flags &= ~OMAPFB_FORMAT_FLAG_TEARSYNC;
	}

	ADD_PREQ(x, ystart, width, yspan, x_out, ystart_out,
		 width_out, yspan_out);
}