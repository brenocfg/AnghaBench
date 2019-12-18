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
struct TYPE_2__ {scalar_t__ update_mode; int /*<<< orphan*/  ext_mode; } ;

/* Variables and functions */
 scalar_t__ OMAPFB_AUTO_UPDATE ; 
 TYPE_1__ dispc ; 
 int /*<<< orphan*/  enable_lcd_clocks (int) ; 
 int /*<<< orphan*/  load_palette () ; 
 int /*<<< orphan*/  omap_dispc_enable_lcd_out (int) ; 
 int /*<<< orphan*/  set_lcd_timings () ; 

__attribute__((used)) static void omap_dispc_resume(void)
{
	if (dispc.update_mode == OMAPFB_AUTO_UPDATE) {
		enable_lcd_clocks(1);
		if (!dispc.ext_mode) {
			set_lcd_timings();
			load_palette();
		}
		omap_dispc_enable_lcd_out(1);
	}
}