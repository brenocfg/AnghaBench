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
struct TYPE_4__ {scalar_t__ update_mode; TYPE_1__* fbdev; int /*<<< orphan*/  frame_done; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ OMAPFB_AUTO_UPDATE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ dispc ; 
 int /*<<< orphan*/  enable_lcd_clocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  omap_dispc_enable_lcd_out (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_dispc_suspend(void)
{
	if (dispc.update_mode == OMAPFB_AUTO_UPDATE) {
		init_completion(&dispc.frame_done);
		omap_dispc_enable_lcd_out(0);
		if (!wait_for_completion_timeout(&dispc.frame_done,
				msecs_to_jiffies(500))) {
			dev_err(dispc.fbdev->dev,
				"timeout waiting for FRAME DONE\n");
		}
		enable_lcd_clocks(0);
	}
}