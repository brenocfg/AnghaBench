#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct plane_info {int width; int height; int out_width; int out_height; } ;
struct TYPE_6__ {int vid_scaled; TYPE_2__* int_ctrl; TYPE_1__* fbdev; struct plane_info* plane; } ;
struct TYPE_5__ {int (* set_scale ) (int,int,int,int,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int OMAPFB_PLANE_NUM ; 
 TYPE_3__ blizzard ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int stub1 (int,int,int,int,int) ; 

__attribute__((used)) static int blizzard_set_scale(int plane, int orig_w, int orig_h,
			      int out_w, int out_h)
{
	struct plane_info *p = &blizzard.plane[plane];
	int r;

	dev_dbg(blizzard.fbdev->dev,
		"plane %d orig_w %d orig_h %d out_w %d out_h %d\n",
		plane, orig_w, orig_h, out_w, out_h);
	if ((unsigned)plane > OMAPFB_PLANE_NUM)
		return -ENODEV;

	r = blizzard.int_ctrl->set_scale(plane, orig_w, orig_h, out_w, out_h);
	if (r < 0)
		return r;

	p->width = orig_w;
	p->height = orig_h;
	p->out_width = out_w;
	p->out_height = out_h;
	if (orig_w == out_w && orig_h == out_h)
		blizzard.vid_scaled &= ~(1 << plane);
	else
		blizzard.vid_scaled |= 1 << plane;

	return 0;
}