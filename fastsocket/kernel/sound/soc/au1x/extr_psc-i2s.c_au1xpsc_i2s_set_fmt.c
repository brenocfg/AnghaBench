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
struct snd_soc_dai {int dummy; } ;
struct au1xpsc_audio_data {unsigned long cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PSC_I2SCFG_BI ; 
 unsigned long PSC_I2SCFG_MLJ ; 
 unsigned long PSC_I2SCFG_MS ; 
 unsigned long PSC_I2SCFG_WI ; 
 unsigned long PSC_I2SCFG_XM ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LSB 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_MSB 130 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 struct au1xpsc_audio_data* au1xpsc_i2s_workdata ; 

__attribute__((used)) static int au1xpsc_i2s_set_fmt(struct snd_soc_dai *cpu_dai,
			       unsigned int fmt)
{
	struct au1xpsc_audio_data *pscdata = au1xpsc_i2s_workdata;
	unsigned long ct;
	int ret;

	ret = -EINVAL;

	ct = pscdata->cfg;

	ct &= ~(PSC_I2SCFG_XM | PSC_I2SCFG_MLJ);	/* left-justified */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ct |= PSC_I2SCFG_XM;	/* enable I2S mode */
		break;
	case SND_SOC_DAIFMT_MSB:
		break;
	case SND_SOC_DAIFMT_LSB:
		ct |= PSC_I2SCFG_MLJ;	/* LSB (right-) justified */
		break;
	default:
		goto out;
	}

	ct &= ~(PSC_I2SCFG_BI | PSC_I2SCFG_WI);		/* IB-IF */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		ct |= PSC_I2SCFG_BI | PSC_I2SCFG_WI;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		ct |= PSC_I2SCFG_BI;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		ct |= PSC_I2SCFG_WI;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		break;
	default:
		goto out;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:	/* CODEC master */
		ct |= PSC_I2SCFG_MS;	/* PSC I2S slave mode */
		break;
	case SND_SOC_DAIFMT_CBS_CFS:	/* CODEC slave */
		ct &= ~PSC_I2SCFG_MS;	/* PSC I2S Master mode */
		break;
	default:
		goto out;
	}

	pscdata->cfg = ct;
	ret = 0;
out:
	return ret;
}