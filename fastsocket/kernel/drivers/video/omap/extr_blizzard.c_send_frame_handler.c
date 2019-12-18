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
struct update_param {int plane; int flags; int /*<<< orphan*/  bpp; int /*<<< orphan*/  color_mode; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  out_y; int /*<<< orphan*/  out_x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_4__ {struct update_param update; } ;
struct blizzard_request {TYPE_1__ par; } ;
struct TYPE_6__ {int enabled_planes; int vid_nonstd_color; int vid_scaled; TYPE_2__* fbdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int OMAPFB_FORMAT_FLAG_DISABLE_OVERLAY ; 
 TYPE_3__ blizzard ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  disable_overlay () ; 
 int do_full_screen_update (struct blizzard_request*) ; 
 int do_partial_update (struct blizzard_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_frame_handler(struct blizzard_request *req)
{
	struct update_param *par = &req->par.update;
	int plane = par->plane;

#ifdef VERBOSE
	dev_dbg(blizzard.fbdev->dev,
		"send_frame: x %d y %d w %d h %d "
		"x_out %d y_out %d w_out %d h_out %d "
		"color_mode %04x flags %04x planes %01x\n",
		par->x, par->y, par->width, par->height,
		par->out_x, par->out_y, par->out_width, par->out_height,
		par->color_mode, par->flags, blizzard.enabled_planes);
#endif
	if (par->flags & OMAPFB_FORMAT_FLAG_DISABLE_OVERLAY)
		disable_overlay();

	if ((blizzard.enabled_planes & blizzard.vid_nonstd_color) ||
	     (blizzard.enabled_planes & blizzard.vid_scaled))
		return do_full_screen_update(req);

	return do_partial_update(req, plane, par->x, par->y,
				 par->width, par->height,
				 par->out_x, par->out_y,
				 par->out_width, par->out_height,
				 par->color_mode, par->bpp);
}