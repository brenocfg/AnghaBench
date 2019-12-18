#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWA742_CLK_SRC_REG ; 
 int /*<<< orphan*/  HWA742_PLL_4_REG ; 
 int /*<<< orphan*/  HWA742_PLL_DIV_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,...) ; 
 TYPE_2__ hwa742 ; 
 int hwa742_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void calc_hwa742_clk_rates(unsigned long ext_clk,
				unsigned long *sys_clk, unsigned long *pix_clk)
{
	int pix_clk_src;
	int sys_div = 0, sys_mul = 0;
	int pix_div;

	pix_clk_src = hwa742_read_reg(HWA742_CLK_SRC_REG);
	pix_div = ((pix_clk_src >> 3) & 0x1f) + 1;
	if ((pix_clk_src & (0x3 << 1)) == 0) {
		/* Source is the PLL */
		sys_div = (hwa742_read_reg(HWA742_PLL_DIV_REG) & 0x3f) + 1;
		sys_mul = (hwa742_read_reg(HWA742_PLL_4_REG) & 0x7f) + 1;
		*sys_clk = ext_clk * sys_mul / sys_div;
	} else	/* else source is ext clk, or oscillator */
		*sys_clk = ext_clk;

	*pix_clk = *sys_clk / pix_div;			/* HZ */
	dev_dbg(hwa742.fbdev->dev,
		"ext_clk %ld pix_src %d pix_div %d sys_div %d sys_mul %d\n",
		ext_clk, pix_clk_src & (0x3 << 1), pix_div, sys_div, sys_mul);
	dev_dbg(hwa742.fbdev->dev, "sys_clk %ld pix_clk %ld\n",
		*sys_clk, *pix_clk);
}