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
struct sm501_devdata {int rev; int /*<<< orphan*/  clock_lock; int /*<<< orphan*/  dev; scalar_t__ regs; } ;
struct sm501_clock {int shift; int divider; int k; int n; int m; int mclk; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  SM501_CLOCK_M1XCLK 131 
#define  SM501_CLOCK_MCLK 130 
#define  SM501_CLOCK_P2XCLK 129 
#define  SM501_CLOCK_V2XCLK 128 
 scalar_t__ SM501_CURRENT_CLOCK ; 
 scalar_t__ SM501_CURRENT_GATE ; 
 scalar_t__ SM501_POWER_MODE_0_CLOCK ; 
 scalar_t__ SM501_POWER_MODE_0_GATE ; 
 scalar_t__ SM501_POWER_MODE_1_CLOCK ; 
 scalar_t__ SM501_POWER_MODE_1_GATE ; 
 scalar_t__ SM501_POWER_MODE_CONTROL ; 
 scalar_t__ SM501_PROGRAMMABLE_PLL_CONTROL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long) ; 
 struct sm501_devdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long readl (scalar_t__) ; 
 int sm501_calc_pll (int,struct sm501_clock*,int) ; 
 int /*<<< orphan*/  sm501_dump_clk (struct sm501_devdata*) ; 
 int /*<<< orphan*/  sm501_mdelay (struct sm501_devdata*,int) ; 
 int sm501_select_clock (unsigned long,struct sm501_clock*,int) ; 
 int /*<<< orphan*/  sm501_sync_regs (struct sm501_devdata*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

unsigned long sm501_set_clock(struct device *dev,
			      int clksrc,
			      unsigned long req_freq)
{
	struct sm501_devdata *sm = dev_get_drvdata(dev);
	unsigned long mode = readl(sm->regs + SM501_POWER_MODE_CONTROL);
	unsigned long gate = readl(sm->regs + SM501_CURRENT_GATE);
	unsigned long clock = readl(sm->regs + SM501_CURRENT_CLOCK);
	unsigned char reg;
	unsigned int pll_reg = 0;
	unsigned long sm501_freq; /* the actual frequency acheived */

	struct sm501_clock to;

	/* find achivable discrete frequency and setup register value
	 * accordingly, V2XCLK, MCLK and M1XCLK are the same P2XCLK
	 * has an extra bit for the divider */

	switch (clksrc) {
	case SM501_CLOCK_P2XCLK:
		/* This clock is divided in half so to achive the
		 * requested frequency the value must be multiplied by
		 * 2. This clock also has an additional pre divisor */

		if (sm->rev >= 0xC0) {
			/* SM502 -> use the programmable PLL */
			sm501_freq = (sm501_calc_pll(2 * req_freq,
						     &to, 5) / 2);
			reg = to.shift & 0x07;/* bottom 3 bits are shift */
			if (to.divider == 3)
				reg |= 0x08; /* /3 divider required */
			else if (to.divider == 5)
				reg |= 0x10; /* /5 divider required */
			reg |= 0x40; /* select the programmable PLL */
			pll_reg = 0x20000 | (to.k << 15) | (to.n << 8) | to.m;
		} else {
			sm501_freq = (sm501_select_clock(2 * req_freq,
							 &to, 5) / 2);
			reg = to.shift & 0x07;/* bottom 3 bits are shift */
			if (to.divider == 3)
				reg |= 0x08; /* /3 divider required */
			else if (to.divider == 5)
				reg |= 0x10; /* /5 divider required */
			if (to.mclk != 288000000)
				reg |= 0x20; /* which mclk pll is source */
		}
		break;

	case SM501_CLOCK_V2XCLK:
		/* This clock is divided in half so to achive the
		 * requested frequency the value must be multiplied by 2. */

		sm501_freq = (sm501_select_clock(2 * req_freq, &to, 3) / 2);
		reg=to.shift & 0x07;	/* bottom 3 bits are shift */
		if (to.divider == 3)
			reg |= 0x08;	/* /3 divider required */
		if (to.mclk != 288000000)
			reg |= 0x10;	/* which mclk pll is source */
		break;

	case SM501_CLOCK_MCLK:
	case SM501_CLOCK_M1XCLK:
		/* These clocks are the same and not further divided */

		sm501_freq = sm501_select_clock( req_freq, &to, 3);
		reg=to.shift & 0x07;	/* bottom 3 bits are shift */
		if (to.divider == 3)
			reg |= 0x08;	/* /3 divider required */
		if (to.mclk != 288000000)
			reg |= 0x10;	/* which mclk pll is source */
		break;

	default:
		return 0; /* this is bad */
	}

	mutex_lock(&sm->clock_lock);

	mode = readl(sm->regs + SM501_POWER_MODE_CONTROL);
	gate = readl(sm->regs + SM501_CURRENT_GATE);
	clock = readl(sm->regs + SM501_CURRENT_CLOCK);

	clock = clock & ~(0xFF << clksrc);
	clock |= reg<<clksrc;

	mode &= 3;	/* find current mode */

	switch (mode) {
	case 1:
		writel(gate, sm->regs + SM501_POWER_MODE_0_GATE);
		writel(clock, sm->regs + SM501_POWER_MODE_0_CLOCK);
		mode = 0;
		break;
	case 2:
	case 0:
		writel(gate, sm->regs + SM501_POWER_MODE_1_GATE);
		writel(clock, sm->regs + SM501_POWER_MODE_1_CLOCK);
		mode = 1;
		break;

	default:
		mutex_unlock(&sm->clock_lock);
		return -1;
	}

	writel(mode, sm->regs + SM501_POWER_MODE_CONTROL);

	if (pll_reg)
		writel(pll_reg, sm->regs + SM501_PROGRAMMABLE_PLL_CONTROL);

	sm501_sync_regs(sm);

	dev_dbg(sm->dev, "gate %08lx, clock %08lx, mode %08lx\n",
		gate, clock, mode);

	sm501_mdelay(sm, 16);
	mutex_unlock(&sm->clock_lock);

	sm501_dump_clk(sm);

	return sm501_freq;
}