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
struct msm_adsp_module {scalar_t__ clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int clk_set_rate (scalar_t__,unsigned long) ; 

int adsp_set_clkrate(struct msm_adsp_module *module, unsigned long clk_rate)
{
	if (module->clk && clk_rate)
		return clk_set_rate(module->clk, clk_rate);

	return -EINVAL;
}