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
struct clk {int /*<<< orphan*/  parent; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {unsigned int divisor; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_TCFG1 ; 
 unsigned long S3C2410_TCFG1_MUX_MASK ; 
 unsigned long S3C2410_TCFG1_SHIFT (int /*<<< orphan*/ ) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ pwm_cfg_src_is_tclk (unsigned long) ; 
 unsigned int tcfg_to_divisor (unsigned long) ; 
 TYPE_1__* to_tdiv (struct clk*) ; 

__attribute__((used)) static unsigned long clk_pwm_tdiv_get_rate(struct clk *clk)
{
	unsigned long tcfg1 = __raw_readl(S3C2410_TCFG1);
	unsigned int divisor;

	tcfg1 >>= S3C2410_TCFG1_SHIFT(clk->id);
	tcfg1 &= S3C2410_TCFG1_MUX_MASK;

	if (pwm_cfg_src_is_tclk(tcfg1))
		divisor = to_tdiv(clk)->divisor;
	else
		divisor = tcfg_to_divisor(tcfg1);

	return clk_get_rate(clk->parent) / divisor;
}