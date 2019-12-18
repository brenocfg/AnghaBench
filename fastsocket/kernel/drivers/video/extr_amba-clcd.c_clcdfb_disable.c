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
struct clcd_fb {int /*<<< orphan*/  clk; scalar_t__ regs; TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct clcd_fb*) ;} ;

/* Variables and functions */
 scalar_t__ CLCD_CNTL ; 
 int CNTL_LCDEN ; 
 int CNTL_LCDPWR ; 
 int /*<<< orphan*/  clcdfb_sleep (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct clcd_fb*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void clcdfb_disable(struct clcd_fb *fb)
{
	u32 val;

	if (fb->board->disable)
		fb->board->disable(fb);

	val = readl(fb->regs + CLCD_CNTL);
	if (val & CNTL_LCDPWR) {
		val &= ~CNTL_LCDPWR;
		writel(val, fb->regs + CLCD_CNTL);

		clcdfb_sleep(20);
	}
	if (val & CNTL_LCDEN) {
		val &= ~CNTL_LCDEN;
		writel(val, fb->regs + CLCD_CNTL);
	}

	/*
	 * Disable CLCD clock source.
	 */
	clk_disable(fb->clk);
}