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
struct pwm_tdiv_clk {unsigned long divisor; } ;
struct clk {int /*<<< orphan*/  id; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S3C2410_TCFG1 ; 
 unsigned long S3C2410_TCFG1_MUX_MASK ; 
 unsigned long S3C2410_TCFG1_SHIFT (int /*<<< orphan*/ ) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_pwm_tdiv_update (struct pwm_tdiv_clk*) ; 
 unsigned long clk_round_rate (struct clk*,unsigned long) ; 
 int /*<<< orphan*/  pwm_cfg_src_is_tclk (unsigned long) ; 
 struct pwm_tdiv_clk* to_tdiv (struct clk*) ; 

__attribute__((used)) static int clk_pwm_tdiv_set_rate(struct clk *clk, unsigned long rate)
{
	struct pwm_tdiv_clk *divclk = to_tdiv(clk);
	unsigned long tcfg1 = __raw_readl(S3C2410_TCFG1);
	unsigned long parent_rate = clk_get_rate(clk->parent);
	unsigned long divisor;

	tcfg1 >>= S3C2410_TCFG1_SHIFT(clk->id);
	tcfg1 &= S3C2410_TCFG1_MUX_MASK;

	rate = clk_round_rate(clk, rate);
	divisor = parent_rate / rate;

	if (divisor > 16)
		return -EINVAL;

	divclk->divisor = divisor;

	/* Update the current MUX settings if we are currently
	 * selected as the clock source for this clock. */

	if (!pwm_cfg_src_is_tclk(tcfg1))
		clk_pwm_tdiv_update(divclk);

	return 0;
}