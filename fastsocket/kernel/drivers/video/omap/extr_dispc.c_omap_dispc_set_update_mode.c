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
typedef  enum omapfb_update_mode { ____Placeholder_omapfb_update_mode } omapfb_update_mode ;
struct TYPE_4__ {int update_mode; TYPE_1__* fbdev; int /*<<< orphan*/  frame_done; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  OMAPFB_AUTO_UPDATE 130 
#define  OMAPFB_MANUAL_UPDATE 129 
#define  OMAPFB_UPDATE_DISABLED 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ dispc ; 
 int /*<<< orphan*/  enable_lcd_clocks (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  omap_dispc_enable_lcd_out (int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_dispc_set_update_mode(enum omapfb_update_mode mode)
{
	int r = 0;

	if (mode != dispc.update_mode) {
		switch (mode) {
		case OMAPFB_AUTO_UPDATE:
		case OMAPFB_MANUAL_UPDATE:
			enable_lcd_clocks(1);
			omap_dispc_enable_lcd_out(1);
			dispc.update_mode = mode;
			break;
		case OMAPFB_UPDATE_DISABLED:
			init_completion(&dispc.frame_done);
			omap_dispc_enable_lcd_out(0);
			if (!wait_for_completion_timeout(&dispc.frame_done,
					msecs_to_jiffies(500))) {
				dev_err(dispc.fbdev->dev,
					 "timeout waiting for FRAME DONE\n");
			}
			dispc.update_mode = mode;
			enable_lcd_clocks(0);
			break;
		default:
			r = -EINVAL;
		}
	}

	return r;
}