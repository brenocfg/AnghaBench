#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u32 ;
typedef  int u16 ;
struct omapfb_plane_struct {int color_mode; struct omapfb_device* fbdev; } ;
struct omapfb_device {TYPE_1__* ctrl; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; } ;
struct TYPE_7__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_6__ {int offset; int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct fb_info {scalar_t__ pseudo_palette; struct fb_var_screeninfo var; struct omapfb_plane_struct* par; } ;
struct TYPE_5__ {int (* setcolreg ) (int,int,int,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  OMAPFB_COLOR_CLUT_1BPP 136 
#define  OMAPFB_COLOR_CLUT_2BPP 135 
#define  OMAPFB_COLOR_CLUT_4BPP 134 
#define  OMAPFB_COLOR_CLUT_8BPP 133 
#define  OMAPFB_COLOR_RGB444 132 
#define  OMAPFB_COLOR_RGB565 131 
#define  OMAPFB_COLOR_YUV420 130 
#define  OMAPFB_COLOR_YUV422 129 
#define  OMAPFB_COLOR_YUY422 128 
 int stub1 (int,int,int,int,int,int) ; 

__attribute__((used)) static int _setcolreg(struct fb_info *info, u_int regno, u_int red, u_int green,
			u_int blue, u_int transp, int update_hw_pal)
{
	struct omapfb_plane_struct *plane = info->par;
	struct omapfb_device *fbdev = plane->fbdev;
	struct fb_var_screeninfo *var = &info->var;
	int r = 0;

	switch (plane->color_mode) {
	case OMAPFB_COLOR_YUV422:
	case OMAPFB_COLOR_YUV420:
	case OMAPFB_COLOR_YUY422:
		r = -EINVAL;
		break;
	case OMAPFB_COLOR_CLUT_8BPP:
	case OMAPFB_COLOR_CLUT_4BPP:
	case OMAPFB_COLOR_CLUT_2BPP:
	case OMAPFB_COLOR_CLUT_1BPP:
		if (fbdev->ctrl->setcolreg)
			r = fbdev->ctrl->setcolreg(regno, red, green, blue,
							transp, update_hw_pal);
		/* Fallthrough */
	case OMAPFB_COLOR_RGB565:
	case OMAPFB_COLOR_RGB444:
		if (r != 0)
			break;

		if (regno < 0) {
			r = -EINVAL;
			break;
		}

		if (regno < 16) {
			u16 pal;
			pal = ((red >> (16 - var->red.length)) <<
					var->red.offset) |
			      ((green >> (16 - var->green.length)) <<
					var->green.offset) |
			      (blue >> (16 - var->blue.length));
			((u32 *)(info->pseudo_palette))[regno] = pal;
		}
		break;
	default:
		BUG();
	}
	return r;
}