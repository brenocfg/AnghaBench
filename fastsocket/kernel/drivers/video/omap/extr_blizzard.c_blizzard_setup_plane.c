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
struct plane_info {int bpp; unsigned long offset; int pos_x; int pos_y; int width; int height; int scr_width; int out_width; int out_height; int color_mode; } ;
struct TYPE_4__ {int vid_nonstd_color; struct plane_info* plane; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  OMAPFB_COLOR_RGB565 131 
#define  OMAPFB_COLOR_YUV420 130 
#define  OMAPFB_COLOR_YUV422 129 
#define  OMAPFB_COLOR_YUY422 128 
 unsigned int OMAPFB_PLANE_NUM ; 
 TYPE_2__ blizzard ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,unsigned long,int,int,int,int,int,int) ; 

__attribute__((used)) static int blizzard_setup_plane(int plane, int channel_out,
				  unsigned long offset, int screen_width,
				  int pos_x, int pos_y, int width, int height,
				  int color_mode)
{
	struct plane_info *p;

#ifdef VERBOSE
	dev_dbg(blizzard.fbdev->dev,
		    "plane %d ch_out %d offset %#08lx scr_width %d "
		    "pos_x %d pos_y %d width %d height %d color_mode %d\n",
		    plane, channel_out, offset, screen_width,
		    pos_x, pos_y, width, height, color_mode);
#endif
	if ((unsigned)plane > OMAPFB_PLANE_NUM)
		return -EINVAL;
	p = &blizzard.plane[plane];

	switch (color_mode) {
	case OMAPFB_COLOR_YUV422:
	case OMAPFB_COLOR_YUY422:
		p->bpp = 16;
		blizzard.vid_nonstd_color &= ~(1 << plane);
		break;
	case OMAPFB_COLOR_YUV420:
		p->bpp = 12;
		blizzard.vid_nonstd_color |= 1 << plane;
		break;
	case OMAPFB_COLOR_RGB565:
		p->bpp = 16;
		blizzard.vid_nonstd_color &= ~(1 << plane);
		break;
	default:
		return -EINVAL;
	}

	p->offset = offset;
	p->pos_x = pos_x;
	p->pos_y = pos_y;
	p->width = width;
	p->height = height;
	p->scr_width = screen_width;
	if (!p->out_width)
		p->out_width = width;
	if (!p->out_height)
		p->out_height = height;

	p->color_mode = color_mode;

	return 0;
}