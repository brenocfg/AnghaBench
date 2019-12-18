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
typedef  int u16 ;
struct TYPE_4__ {int palette_code; int palette_size; int ext_mode; TYPE_1__* fbdev; int /*<<< orphan*/  palette_load_complete; int /*<<< orphan*/  palette_phys; scalar_t__ palette_virt; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DMA_DATA_TYPE_S32 ; 
 int /*<<< orphan*/  OMAP_LCDC_IRQ_LOADED_PALETTE ; 
 int /*<<< orphan*/  OMAP_LCDC_LOAD_PALETTE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_irqs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_controller () ; 
 int /*<<< orphan*/  enable_irqs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 TYPE_2__ lcdc ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  omap_set_lcd_dma_b1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_lcd_dma_single_transfer (int) ; 
 int /*<<< orphan*/  omap_setup_lcd_dma () ; 
 int /*<<< orphan*/  omap_stop_lcd_dma () ; 
 int /*<<< orphan*/  set_load_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_palette(void)
{
	u16	*palette;

	palette = (u16 *)lcdc.palette_virt;

	*(u16 *)palette &= 0x0fff;
	*(u16 *)palette |= lcdc.palette_code;

	omap_set_lcd_dma_b1(lcdc.palette_phys,
		lcdc.palette_size / 4 + 1, 1, OMAP_DMA_DATA_TYPE_S32);

	omap_set_lcd_dma_single_transfer(1);
	omap_setup_lcd_dma();

	init_completion(&lcdc.palette_load_complete);
	enable_irqs(OMAP_LCDC_IRQ_LOADED_PALETTE);
	set_load_mode(OMAP_LCDC_LOAD_PALETTE);
	enable_controller();
	if (!wait_for_completion_timeout(&lcdc.palette_load_complete,
				msecs_to_jiffies(500)))
		dev_err(lcdc.fbdev->dev, "timeout waiting for FRAME DONE\n");
	/* The controller gets disabled in the irq handler */
	disable_irqs(OMAP_LCDC_IRQ_LOADED_PALETTE);
	omap_stop_lcd_dma();

	omap_set_lcd_dma_single_transfer(lcdc.ext_mode);
}