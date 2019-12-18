#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_LCDC_CONTROL ; 
 int OMAP_LCDC_CTRL_LCD_EN ; 
 int OMAP_LCDC_IRQ_DONE ; 
 int OMAP_LCDC_IRQ_MASK ; 
 int omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_controller_async(void)
{
	u32 l;
	u32 mask;

	l = omap_readl(OMAP_LCDC_CONTROL);
	mask = OMAP_LCDC_CTRL_LCD_EN | OMAP_LCDC_IRQ_MASK;
	/*
	 * Preserve the DONE mask, since we still want to get the
	 * final DONE irq. It will be disabled in the IRQ handler.
	 */
	mask &= ~OMAP_LCDC_IRQ_DONE;
	l &= ~mask;
	omap_writel(l, OMAP_LCDC_CONTROL);
}