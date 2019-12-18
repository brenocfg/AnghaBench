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
typedef  int /*<<< orphan*/  u32 ;
struct clcd_fb {TYPE_1__* board; scalar_t__ regs; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct clcd_fb*) ;} ;

/* Variables and functions */
 scalar_t__ CLCD_CNTL ; 
 int /*<<< orphan*/  CNTL_LCDEN ; 
 int /*<<< orphan*/  CNTL_LCDPWR ; 
 int /*<<< orphan*/  clcdfb_sleep (int) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clcd_fb*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void clcdfb_enable(struct clcd_fb *fb, u32 cntl)
{
	/*
	 * Enable the CLCD clock source.
	 */
	clk_enable(fb->clk);

	/*
	 * Bring up by first enabling..
	 */
	cntl |= CNTL_LCDEN;
	writel(cntl, fb->regs + CLCD_CNTL);

	clcdfb_sleep(20);

	/*
	 * and now apply power.
	 */
	cntl |= CNTL_LCDPWR;
	writel(cntl, fb->regs + CLCD_CNTL);

	/*
	 * finally, enable the interface.
	 */
	if (fb->board->enable)
		fb->board->enable(fb);
}