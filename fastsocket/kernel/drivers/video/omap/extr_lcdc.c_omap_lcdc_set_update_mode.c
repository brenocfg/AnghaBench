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
typedef  enum omapfb_update_mode { ____Placeholder_omapfb_update_mode } omapfb_update_mode ;
struct TYPE_2__ {int update_mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  OMAPFB_AUTO_UPDATE 129 
#define  OMAPFB_UPDATE_DISABLED 128 
 int /*<<< orphan*/  OMAP_LCDC_IRQ_DONE ; 
 int /*<<< orphan*/  OMAP_LCDC_LOAD_FRAME ; 
 int /*<<< orphan*/  disable_controller () ; 
 int /*<<< orphan*/  enable_controller () ; 
 int /*<<< orphan*/  enable_irqs (int /*<<< orphan*/ ) ; 
 TYPE_1__ lcdc ; 
 int /*<<< orphan*/  load_palette () ; 
 int /*<<< orphan*/  omap_stop_lcd_dma () ; 
 int /*<<< orphan*/  set_load_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_lcd_dma () ; 
 int /*<<< orphan*/  setup_regs () ; 

__attribute__((used)) static int omap_lcdc_set_update_mode(enum omapfb_update_mode mode)
{
	int r = 0;

	if (mode != lcdc.update_mode) {
		switch (mode) {
		case OMAPFB_AUTO_UPDATE:
			setup_regs();
			load_palette();

			/* Setup and start LCD DMA */
			setup_lcd_dma();

			set_load_mode(OMAP_LCDC_LOAD_FRAME);
			enable_irqs(OMAP_LCDC_IRQ_DONE);
			/* This will start the actual DMA transfer */
			enable_controller();
			lcdc.update_mode = mode;
			break;
		case OMAPFB_UPDATE_DISABLED:
			disable_controller();
			omap_stop_lcd_dma();
			lcdc.update_mode = mode;
			break;
		default:
			r = -EINVAL;
		}
	}

	return r;
}