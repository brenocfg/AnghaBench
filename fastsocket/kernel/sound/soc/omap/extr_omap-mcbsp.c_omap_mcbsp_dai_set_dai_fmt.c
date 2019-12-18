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
struct omap_mcbsp_reg_cfg {int spcr2; int xccr; int rccr; int pcr0; int /*<<< orphan*/  srgr2; int /*<<< orphan*/  xcr2; int /*<<< orphan*/  rcr2; int /*<<< orphan*/  spcr1; } ;
struct omap_mcbsp_data {unsigned int fmt; scalar_t__ configured; struct omap_mcbsp_reg_cfg regs; } ;

/* Variables and functions */
 int CLKRM ; 
 int CLKRP ; 
 int CLKXM ; 
 int CLKXP ; 
 int DXENDLY (int) ; 
 int EINVAL ; 
 int FREE ; 
 int /*<<< orphan*/  FSGM ; 
 int FSRM ; 
 int FSRP ; 
 int FSXM ; 
 int FSXP ; 
 int /*<<< orphan*/  RDATDLY (int) ; 
 int RDISABLE ; 
 int RDMAEN ; 
 int /*<<< orphan*/  RFIG ; 
 int RFULL_CYCLE ; 
 int /*<<< orphan*/  RINTM (int) ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
#define  SND_SOC_DAIFMT_DSP_A 134 
#define  SND_SOC_DAIFMT_DSP_B 133 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 132 
#define  SND_SOC_DAIFMT_IB_IF 131 
#define  SND_SOC_DAIFMT_IB_NF 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  XDATDLY (int) ; 
 int XDISABLE ; 
 int XDMAEN ; 
 int /*<<< orphan*/  XFIG ; 
 int XINTM (int) ; 
 scalar_t__ cpu_is_omap2430 () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 int /*<<< orphan*/  memset (struct omap_mcbsp_reg_cfg*,int /*<<< orphan*/ ,int) ; 
 struct omap_mcbsp_data* to_mcbsp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_mcbsp_dai_set_dai_fmt(struct snd_soc_dai *cpu_dai,
				      unsigned int fmt)
{
	struct omap_mcbsp_data *mcbsp_data = to_mcbsp(cpu_dai->private_data);
	struct omap_mcbsp_reg_cfg *regs = &mcbsp_data->regs;
	unsigned int temp_fmt = fmt;

	if (mcbsp_data->configured)
		return 0;

	mcbsp_data->fmt = fmt;
	memset(regs, 0, sizeof(*regs));
	/* Generic McBSP register settings */
	regs->spcr2	|= XINTM(3) | FREE;
	regs->spcr1	|= RINTM(3);
	/* RFIG and XFIG are not defined in 34xx */
	if (!cpu_is_omap34xx()) {
		regs->rcr2	|= RFIG;
		regs->xcr2	|= XFIG;
	}
	if (cpu_is_omap2430() || cpu_is_omap34xx()) {
		regs->xccr = DXENDLY(1) | XDMAEN | XDISABLE;
		regs->rccr = RFULL_CYCLE | RDMAEN | RDISABLE;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* 1-bit data delay */
		regs->rcr2	|= RDATDLY(1);
		regs->xcr2	|= XDATDLY(1);
		break;
	case SND_SOC_DAIFMT_DSP_A:
		/* 1-bit data delay */
		regs->rcr2      |= RDATDLY(1);
		regs->xcr2      |= XDATDLY(1);
		/* Invert FS polarity configuration */
		temp_fmt ^= SND_SOC_DAIFMT_NB_IF;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		/* 0-bit data delay */
		regs->rcr2      |= RDATDLY(0);
		regs->xcr2      |= XDATDLY(0);
		/* Invert FS polarity configuration */
		temp_fmt ^= SND_SOC_DAIFMT_NB_IF;
		break;
	default:
		/* Unsupported data format */
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		/* McBSP master. Set FS and bit clocks as outputs */
		regs->pcr0	|= FSXM | FSRM |
				   CLKXM | CLKRM;
		/* Sample rate generator drives the FS */
		regs->srgr2	|= FSGM;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		/* McBSP slave */
		break;
	default:
		/* Unsupported master/slave configuration */
		return -EINVAL;
	}

	/* Set bit clock (CLKX/CLKR) and FS polarities */
	switch (temp_fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		/*
		 * Normal BCLK + FS.
		 * FS active low. TX data driven on falling edge of bit clock
		 * and RX data sampled on rising edge of bit clock.
		 */
		regs->pcr0	|= FSXP | FSRP |
				   CLKXP | CLKRP;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		regs->pcr0	|= CLKXP | CLKRP;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		regs->pcr0	|= FSXP | FSRP;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		break;
	default:
		return -EINVAL;
	}

	return 0;
}