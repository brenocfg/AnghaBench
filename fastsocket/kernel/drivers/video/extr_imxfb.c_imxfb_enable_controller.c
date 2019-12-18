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
struct imxfb_info {int screen_dma; int /*<<< orphan*/  (* lcd_power ) (int) ;int /*<<< orphan*/  (* backlight_power ) (int) ;int /*<<< orphan*/  clk; scalar_t__ regs; } ;

/* Variables and functions */
 int CPOS_CC0 ; 
 int CPOS_CC1 ; 
 scalar_t__ LCDC_CPOS ; 
 scalar_t__ LCDC_POS ; 
 scalar_t__ LCDC_RMCR ; 
 scalar_t__ LCDC_SSA ; 
 int RMCR_LCDC_EN ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void imxfb_enable_controller(struct imxfb_info *fbi)
{
	pr_debug("Enabling LCD controller\n");

	writel(fbi->screen_dma, fbi->regs + LCDC_SSA);

	/* panning offset 0 (0 pixel offset)        */
	writel(0x00000000, fbi->regs + LCDC_POS);

	/* disable hardware cursor */
	writel(readl(fbi->regs + LCDC_CPOS) & ~(CPOS_CC0 | CPOS_CC1),
		fbi->regs + LCDC_CPOS);

	writel(RMCR_LCDC_EN, fbi->regs + LCDC_RMCR);

	clk_enable(fbi->clk);

	if (fbi->backlight_power)
		fbi->backlight_power(1);
	if (fbi->lcd_power)
		fbi->lcd_power(1);
}