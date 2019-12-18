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
struct TYPE_2__ {scalar_t__ update_mode; } ;

/* Variables and functions */
 scalar_t__ OMAPFB_AUTO_UPDATE ; 
 int /*<<< orphan*/  OMAP_LCDC_IRQ_DONE ; 
 int /*<<< orphan*/  OMAP_LCDC_LOAD_FRAME ; 
 int /*<<< orphan*/  enable_controller () ; 
 int /*<<< orphan*/  enable_irqs (int /*<<< orphan*/ ) ; 
 TYPE_1__ lcdc ; 
 int /*<<< orphan*/  load_palette () ; 
 int /*<<< orphan*/  set_load_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_lcd_dma () ; 
 int /*<<< orphan*/  setup_regs () ; 

__attribute__((used)) static void omap_lcdc_resume(void)
{
	if (lcdc.update_mode == OMAPFB_AUTO_UPDATE) {
		setup_regs();
		load_palette();
		setup_lcd_dma();
		set_load_mode(OMAP_LCDC_LOAD_FRAME);
		enable_irqs(OMAP_LCDC_IRQ_DONE);
		enable_controller();
	}
}