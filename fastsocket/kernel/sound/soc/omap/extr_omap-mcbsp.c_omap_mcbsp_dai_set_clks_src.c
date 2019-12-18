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
typedef  int /*<<< orphan*/  u16 ;
struct omap_mcbsp_data {int bus_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP243X_CONTROL_DEVCONF1 ; 
 int /*<<< orphan*/  OMAP2_CONTROL_DEVCONF0 ; 
 int /*<<< orphan*/  OMAP343X_CONTROL_DEVCONF1 ; 
 int OMAP_MCBSP_SYSCLK_CLKS_FCLK ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_is_omap2420 () ; 
 scalar_t__ cpu_is_omap343x () ; 
 int omap_ctrl_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ctrl_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int omap_mcbsp_dai_set_clks_src(struct omap_mcbsp_data *mcbsp_data,
				       int clk_id)
{
	int sel_bit;
	u16 reg, reg_devconf1 = OMAP243X_CONTROL_DEVCONF1;

	if (cpu_class_is_omap1()) {
		/* OMAP1's can use only external source clock */
		if (unlikely(clk_id == OMAP_MCBSP_SYSCLK_CLKS_FCLK))
			return -EINVAL;
		else
			return 0;
	}

	if (cpu_is_omap2420() && mcbsp_data->bus_id > 1)
		return -EINVAL;

	if (cpu_is_omap343x())
		reg_devconf1 = OMAP343X_CONTROL_DEVCONF1;

	switch (mcbsp_data->bus_id) {
	case 0:
		reg = OMAP2_CONTROL_DEVCONF0;
		sel_bit = 2;
		break;
	case 1:
		reg = OMAP2_CONTROL_DEVCONF0;
		sel_bit = 6;
		break;
	case 2:
		reg = reg_devconf1;
		sel_bit = 0;
		break;
	case 3:
		reg = reg_devconf1;
		sel_bit = 2;
		break;
	case 4:
		reg = reg_devconf1;
		sel_bit = 4;
		break;
	default:
		return -EINVAL;
	}

	if (clk_id == OMAP_MCBSP_SYSCLK_CLKS_FCLK)
		omap_ctrl_writel(omap_ctrl_readl(reg) & ~(1 << sel_bit), reg);
	else
		omap_ctrl_writel(omap_ctrl_readl(reg) | (1 << sel_bit), reg);

	return 0;
}