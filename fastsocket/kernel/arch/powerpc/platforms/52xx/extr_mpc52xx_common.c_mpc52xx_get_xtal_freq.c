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
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rstcfg; int /*<<< orphan*/  ipb_clk_sel; } ;

/* Variables and functions */
 int in_8 (int /*<<< orphan*/ *) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 TYPE_1__* mpc52xx_cdm ; 
 unsigned int mpc5xxx_get_bus_frequency (struct device_node*) ; 

unsigned int mpc52xx_get_xtal_freq(struct device_node *node)
{
	u32 val;
	unsigned int freq;

	if (!mpc52xx_cdm)
		return 0;

	freq = mpc5xxx_get_bus_frequency(node);
	if (!freq)
		return 0;

	if (in_8(&mpc52xx_cdm->ipb_clk_sel) & 0x1)
		freq *= 2;

	val  = in_be32(&mpc52xx_cdm->rstcfg);
	if (val & (1 << 5))
		freq *= 8;
	else
		freq *= 4;
	if (val & (1 << 6))
		freq /= 12;
	else
		freq /= 16;

	return freq;
}