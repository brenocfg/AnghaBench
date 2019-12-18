#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct plane_info {int /*<<< orphan*/  color_mode; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; int /*<<< orphan*/  scr_width; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_10__ {TYPE_3__ update; } ;
struct blizzard_request {TYPE_4__ par; } ;
struct TYPE_12__ {int enabled_planes; int /*<<< orphan*/  screen_height; int /*<<< orphan*/  screen_width; TYPE_5__* extif; scalar_t__ zoom_on; TYPE_2__* fbdev; TYPE_1__* int_ctrl; struct plane_info* plane; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* transfer_area ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct blizzard_request*) ;int /*<<< orphan*/  (* set_bits_per_cycle ) (int) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* enable_plane ) (int,int) ;int /*<<< orphan*/  (* setup_plane ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLIZZARD_COLOR_RGB565 ; 
 int /*<<< orphan*/  OMAPFB_CHANNEL_OUT_LCD ; 
 int OMAPFB_FORMAT_FLAG_FORCE_VSYNC ; 
 int OMAPFB_FORMAT_FLAG_TEARSYNC ; 
 int REQ_PENDING ; 
 TYPE_6__ blizzard ; 
 int /*<<< orphan*/  blizzard_wait_line_buffer () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_tearsync () ; 
 int /*<<< orphan*/  enable_tearsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_complete ; 
 int /*<<< orphan*/  set_window_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int) ; 
 int /*<<< orphan*/  stub4 (int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct blizzard_request*) ; 

__attribute__((used)) static int do_full_screen_update(struct blizzard_request *req)
{
	int i;
	int flags;

	for (i = 0; i < 3; i++) {
		struct plane_info *p = &blizzard.plane[i];
		if (!(blizzard.enabled_planes & (1 << i))) {
			blizzard.int_ctrl->enable_plane(i, 0);
			continue;
		}
		dev_dbg(blizzard.fbdev->dev, "pw %d ph %d\n",
			p->width, p->height);
		blizzard.int_ctrl->setup_plane(i,
				OMAPFB_CHANNEL_OUT_LCD, p->offset,
				p->scr_width, p->pos_x, p->pos_y,
				p->width, p->height,
				p->color_mode);
		blizzard.int_ctrl->enable_plane(i, 1);
	}

	dev_dbg(blizzard.fbdev->dev, "sw %d sh %d\n",
		blizzard.screen_width, blizzard.screen_height);
	blizzard_wait_line_buffer();
	flags = req->par.update.flags;
	if (flags & OMAPFB_FORMAT_FLAG_TEARSYNC)
		enable_tearsync(0, blizzard.screen_width,
				blizzard.screen_height,
				blizzard.screen_height,
				blizzard.screen_height,
				flags & OMAPFB_FORMAT_FLAG_FORCE_VSYNC);
	else
		disable_tearsync();

	set_window_regs(0, 0, blizzard.screen_width, blizzard.screen_height,
			0, 0, blizzard.screen_width, blizzard.screen_height,
			BLIZZARD_COLOR_RGB565, blizzard.zoom_on, flags);
	blizzard.zoom_on = 0;

	blizzard.extif->set_bits_per_cycle(16);
	/* set_window_regs has left the register index at the right
	 * place, so no need to set it here.
	 */
	blizzard.extif->transfer_area(blizzard.screen_width,
				      blizzard.screen_height,
				      request_complete, req);
	return REQ_PENDING;
}