#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct geodefb_par {scalar_t__ vid_regs; } ;
struct TYPE_4__ {long pixclock; } ;
struct fb_info {TYPE_1__ var; struct geodefb_par* par; } ;
struct TYPE_5__ {int pll_value; long pixclock; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ CS5530_DOT_CLK_CONFIG ; 
 TYPE_2__* cs5530_pll_table ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cs5530_set_dclk_frequency(struct fb_info *info)
{
	struct geodefb_par *par = info->par;
	int i;
	u32 value;
	long min, diff;

	/* Search the table for the closest pixclock. */
	value = cs5530_pll_table[0].pll_value;
	min = cs5530_pll_table[0].pixclock - info->var.pixclock;
	if (min < 0) min = -min;
	for (i = 1; i < ARRAY_SIZE(cs5530_pll_table); i++) {
		diff = cs5530_pll_table[i].pixclock - info->var.pixclock;
		if (diff < 0L) diff = -diff;
		if (diff < min) {
			min = diff;
			value = cs5530_pll_table[i].pll_value;
		}
	}

	writel(value, par->vid_regs + CS5530_DOT_CLK_CONFIG);
	writel(value | 0x80000100, par->vid_regs + CS5530_DOT_CLK_CONFIG); /* set reset and bypass */
	udelay(500); /* wait for PLL to settle */
	writel(value & 0x7FFFFFFF, par->vid_regs + CS5530_DOT_CLK_CONFIG); /* clear reset */
	writel(value & 0x7FFFFEFF, par->vid_regs + CS5530_DOT_CLK_CONFIG); /* clear bypass */
}