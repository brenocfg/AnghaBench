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
struct sa1111 {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ SA1111_SKCR ; 
 scalar_t__ SA1111_SKPCR ; 
 unsigned long SKCR_OE_EN ; 
 unsigned long SKCR_PLL_BYPASS ; 
 unsigned long SKCR_RCLKEN ; 
 unsigned long SKCR_RDYEN ; 
 unsigned long SKCR_VCO_OFF ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 unsigned long sa1111_readl (scalar_t__) ; 
 int /*<<< orphan*/  sa1111_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sa1111_wake(struct sa1111 *sachip)
{
	unsigned long flags, r;

	spin_lock_irqsave(&sachip->lock, flags);

	clk_enable(sachip->clk);

	/*
	 * Turn VCO on, and disable PLL Bypass.
	 */
	r = sa1111_readl(sachip->base + SA1111_SKCR);
	r &= ~SKCR_VCO_OFF;
	sa1111_writel(r, sachip->base + SA1111_SKCR);
	r |= SKCR_PLL_BYPASS | SKCR_OE_EN;
	sa1111_writel(r, sachip->base + SA1111_SKCR);

	/*
	 * Wait lock time.  SA1111 manual _doesn't_
	 * specify a figure for this!  We choose 100us.
	 */
	udelay(100);

	/*
	 * Enable RCLK.  We also ensure that RDYEN is set.
	 */
	r |= SKCR_RCLKEN | SKCR_RDYEN;
	sa1111_writel(r, sachip->base + SA1111_SKCR);

	/*
	 * Wait 14 RCLK cycles for the chip to finish coming out
	 * of reset. (RCLK=24MHz).  This is 590ns.
	 */
	udelay(1);

	/*
	 * Ensure all clocks are initially off.
	 */
	sa1111_writel(0, sachip->base + SA1111_SKPCR);

	spin_unlock_irqrestore(&sachip->lock, flags);
}