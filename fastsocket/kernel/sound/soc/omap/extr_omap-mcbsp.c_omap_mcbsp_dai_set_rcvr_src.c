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
struct omap_mcbsp_data {scalar_t__ bus_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OMAP2_CONTROL_DEVCONF0 ; 
#define  OMAP_MCBSP_CLKR_SRC_CLKR 131 
#define  OMAP_MCBSP_CLKR_SRC_CLKX 130 
#define  OMAP_MCBSP_FSR_SRC_FSR 129 
#define  OMAP_MCBSP_FSR_SRC_FSX 128 
 scalar_t__ cpu_class_is_omap1 () ; 
 int omap_ctrl_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ctrl_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_mcbsp_dai_set_rcvr_src(struct omap_mcbsp_data *mcbsp_data,
				       int clk_id)
{
	int sel_bit, set = 0;
	u16 reg = OMAP2_CONTROL_DEVCONF0;

	if (cpu_class_is_omap1())
		return -EINVAL; /* TODO: Can this be implemented for OMAP1? */
	if (mcbsp_data->bus_id != 0)
		return -EINVAL;

	switch (clk_id) {
	case OMAP_MCBSP_CLKR_SRC_CLKX:
		set = 1;
	case OMAP_MCBSP_CLKR_SRC_CLKR:
		sel_bit = 3;
		break;
	case OMAP_MCBSP_FSR_SRC_FSX:
		set = 1;
	case OMAP_MCBSP_FSR_SRC_FSR:
		sel_bit = 4;
		break;
	default:
		return -EINVAL;
	}

	if (set)
		omap_ctrl_writel(omap_ctrl_readl(reg) | (1 << sel_bit), reg);
	else
		omap_ctrl_writel(omap_ctrl_readl(reg) & ~(1 << sel_bit), reg);

	return 0;
}