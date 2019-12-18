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
struct imxfb_info {scalar_t__ regs; int /*<<< orphan*/  clk; int /*<<< orphan*/  (* lcd_power ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* backlight_power ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ LCDC_RMCR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void imxfb_disable_controller(struct imxfb_info *fbi)
{
	pr_debug("Disabling LCD controller\n");

	if (fbi->backlight_power)
		fbi->backlight_power(0);
	if (fbi->lcd_power)
		fbi->lcd_power(0);

	clk_disable(fbi->clk);

	writel(0, fbi->regs + LCDC_RMCR);
}