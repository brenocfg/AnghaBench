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
struct clk {int rate; int /*<<< orphan*/  enable_reg; } ;
typedef  int __u16 ;

/* Variables and functions */
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap1_init_ext_clk(struct clk * clk)
{
	unsigned dsor;
	__u16 ratio_bits;

	/* Determine current rate and ensure clock is based on 96MHz APLL */
	ratio_bits = __raw_readw(clk->enable_reg) & ~1;
	__raw_writew(ratio_bits, clk->enable_reg);

	ratio_bits = (ratio_bits & 0xfc) >> 2;
	if (ratio_bits > 6)
		dsor = (ratio_bits - 6) * 2 + 8;
	else
		dsor = ratio_bits + 2;

	clk-> rate = 96000000 / dsor;
}