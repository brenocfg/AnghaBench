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
struct snd_soc_dai {int /*<<< orphan*/  private_data; } ;
struct omap_mcbsp_reg_cfg {int /*<<< orphan*/  pcr0; int /*<<< orphan*/  srgr2; } ;
struct omap_mcbsp_data {struct omap_mcbsp_reg_cfg regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKSM ; 
 int ENODEV ; 
#define  OMAP_MCBSP_CLKR_SRC_CLKR 136 
#define  OMAP_MCBSP_CLKR_SRC_CLKX 135 
#define  OMAP_MCBSP_FSR_SRC_FSR 134 
#define  OMAP_MCBSP_FSR_SRC_FSX 133 
#define  OMAP_MCBSP_SYSCLK_CLK 132 
#define  OMAP_MCBSP_SYSCLK_CLKR_EXT 131 
#define  OMAP_MCBSP_SYSCLK_CLKS_EXT 130 
#define  OMAP_MCBSP_SYSCLK_CLKS_FCLK 129 
#define  OMAP_MCBSP_SYSCLK_CLKX_EXT 128 
 int /*<<< orphan*/  SCLKME ; 
 int omap_mcbsp_dai_set_clks_src (struct omap_mcbsp_data*,int) ; 
 int omap_mcbsp_dai_set_rcvr_src (struct omap_mcbsp_data*,int) ; 
 struct omap_mcbsp_data* to_mcbsp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_mcbsp_dai_set_dai_sysclk(struct snd_soc_dai *cpu_dai,
					 int clk_id, unsigned int freq,
					 int dir)
{
	struct omap_mcbsp_data *mcbsp_data = to_mcbsp(cpu_dai->private_data);
	struct omap_mcbsp_reg_cfg *regs = &mcbsp_data->regs;
	int err = 0;

	switch (clk_id) {
	case OMAP_MCBSP_SYSCLK_CLK:
		regs->srgr2	|= CLKSM;
		break;
	case OMAP_MCBSP_SYSCLK_CLKS_FCLK:
	case OMAP_MCBSP_SYSCLK_CLKS_EXT:
		err = omap_mcbsp_dai_set_clks_src(mcbsp_data, clk_id);
		break;

	case OMAP_MCBSP_SYSCLK_CLKX_EXT:
		regs->srgr2	|= CLKSM;
	case OMAP_MCBSP_SYSCLK_CLKR_EXT:
		regs->pcr0	|= SCLKME;
		break;

	case OMAP_MCBSP_CLKR_SRC_CLKR:
	case OMAP_MCBSP_CLKR_SRC_CLKX:
	case OMAP_MCBSP_FSR_SRC_FSR:
	case OMAP_MCBSP_FSR_SRC_FSX:
		err = omap_mcbsp_dai_set_rcvr_src(mcbsp_data, clk_id);
		break;
	default:
		err = -ENODEV;
	}

	return err;
}