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
struct clk {scalar_t__ busy_reg; scalar_t__ scale_reg; TYPE_1__* parent; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int BF (int,int /*<<< orphan*/ ) ; 
 int BM_CLKCTRL_CLKSEQ_BYPASS_PIX ; 
 int /*<<< orphan*/  BM_CLKCTRL_FRAC_CLKGATEPIX ; 
 int BM_CLKCTRL_FRAC_PIXFRAC ; 
 int BM_CLKCTRL_PIX_CLKGATE ; 
 int BM_CLKCTRL_PIX_DIV ; 
 int /*<<< orphan*/  CLKCTRL_FRAC_PIXFRAC ; 
 int /*<<< orphan*/  CLKCTRL_PIX_DIV ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ HW_CLKCTRL_CLKSEQ ; 
 scalar_t__ HW_CLKCTRL_FRAC ; 
 scalar_t__ REGS_CLKCTRL_BASE ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  clk_is_busy (struct clk*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lcdif_set_rate(struct clk *clk, u32 rate)
{
	int ret = 0;
	/*
	 * On 3700, we can get most timings exact by modifying ref_pix
	 * and the divider, but keeping the phase timings at 1 (2
	 * phases per cycle).
	 *
	 * ref_pix can be between 480e6*18/35=246.9MHz and 480e6*18/18=480MHz,
	 * which is between 18/(18*480e6)=2.084ns and 35/(18*480e6)=4.050ns.
	 *
	 * ns_cycle >= 2*18e3/(18*480) = 25/6
	 * ns_cycle <= 2*35e3/(18*480) = 875/108
	 *
	 * Multiply the ns_cycle by 'div' to lengthen it until it fits the
	 * bounds. This is the divider we'll use after ref_pix.
	 *
	 * 6 * ns_cycle >= 25 * div
	 * 108 * ns_cycle <= 875 * div
	 */
	u32 ns_cycle = 1000000 / rate;
	u32 div, reg_val;
	u32 lowest_result = (u32) -1;
	u32 lowest_div = 0, lowest_fracdiv = 0;

	for (div = 1; div < 256; ++div) {
		u32 fracdiv;
		u32 ps_result;
		int lower_bound = 6 * ns_cycle >= 25 * div;
		int upper_bound = 108 * ns_cycle <= 875 * div;
		if (!lower_bound)
			break;
		if (!upper_bound)
			continue;
		/*
		 * Found a matching div. Calculate fractional divider needed,
		 * rounded up.
		 */
		fracdiv = ((clk->parent->rate / 1000 * 18 / 2) *
				ns_cycle + 1000 * div - 1) /
				(1000 * div);
		if (fracdiv < 18 || fracdiv > 35) {
			ret = -EINVAL;
			goto out;
		}
		/* Calculate the actual cycle time this results in */
		ps_result = 6250 * div * fracdiv / 27;

		/* Use the fastest result that doesn't break ns_cycle */
		if (ps_result <= lowest_result) {
			lowest_result = ps_result;
			lowest_div = div;
			lowest_fracdiv = fracdiv;
		}
	}

	if (div >= 256 || lowest_result == (u32) -1) {
		ret = -EINVAL;
		goto out;
	}
	pr_debug("Programming PFD=%u,DIV=%u ref_pix=%uMHz "
			"PIXCLK=%uMHz cycle=%u.%03uns\n",
			lowest_fracdiv, lowest_div,
			480*18/lowest_fracdiv, 480*18/lowest_fracdiv/lowest_div,
			lowest_result / 1000, lowest_result % 1000);

	/* Program ref_pix phase fractional divider */
	reg_val = __raw_readl(REGS_CLKCTRL_BASE + HW_CLKCTRL_FRAC);
	reg_val &= ~BM_CLKCTRL_FRAC_PIXFRAC;
	reg_val |= BF(lowest_fracdiv, CLKCTRL_FRAC_PIXFRAC);
	__raw_writel(reg_val, REGS_CLKCTRL_BASE + HW_CLKCTRL_FRAC);

	/* Ungate PFD */
	stmp3xxx_clearl(BM_CLKCTRL_FRAC_CLKGATEPIX,
			REGS_CLKCTRL_BASE + HW_CLKCTRL_FRAC);

	/* Program pix divider */
	reg_val = __raw_readl(clk->scale_reg);
	reg_val &= ~(BM_CLKCTRL_PIX_DIV | BM_CLKCTRL_PIX_CLKGATE);
	reg_val |= BF(lowest_div, CLKCTRL_PIX_DIV);
	__raw_writel(reg_val, clk->scale_reg);

	/* Wait for divider update */
	if (clk->busy_reg) {
		int i;
		for (i = 10000; i; i--)
			if (!clk_is_busy(clk))
				break;
		if (!i) {
			ret = -ETIMEDOUT;
			goto out;
		}
	}

	/* Switch to ref_pix source */
	reg_val = __raw_readl(REGS_CLKCTRL_BASE + HW_CLKCTRL_CLKSEQ);
	reg_val &= ~BM_CLKCTRL_CLKSEQ_BYPASS_PIX;
	__raw_writel(reg_val, REGS_CLKCTRL_BASE + HW_CLKCTRL_CLKSEQ);

out:
	return ret;
}