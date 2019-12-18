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
typedef  int u32 ;
struct TYPE_2__ {int irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_LCDC_CONTROL ; 
 int OMAP_LCDC_CTRL_LCD_EN ; 
 int OMAP_LCDC_IRQ_DONE ; 
 int OMAP_LCDC_IRQ_MASK ; 
 TYPE_1__ lcdc ; 
 int omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_controller(void)
{
	u32 l;

	l = omap_readl(OMAP_LCDC_CONTROL);
	l |= OMAP_LCDC_CTRL_LCD_EN;
	l &= ~OMAP_LCDC_IRQ_MASK;
	l |= lcdc.irq_mask | OMAP_LCDC_IRQ_DONE;	/* enabled IRQs */
	omap_writel(l, OMAP_LCDC_CONTROL);
}