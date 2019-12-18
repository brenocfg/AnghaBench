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
typedef  int u32 ;
struct snd_soc_dai {struct s6000_i2s_dev* private_data; } ;
struct s6000_i2s_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int S6_I2S_FIRST ; 
 int /*<<< orphan*/  S6_I2S_INTERFACE_CFG (int) ; 
 int S6_I2S_LEFT_FIRST ; 
 int S6_I2S_RIGHT_FIRST ; 
 int S6_I2S_SCK_DIR ; 
 int S6_I2S_SCK_IN ; 
 int S6_I2S_SCK_OUT ; 
 int S6_I2S_WS_DIR ; 
 int S6_I2S_WS_IN ; 
 int S6_I2S_WS_OUT ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBM_CFS 132 
#define  SND_SOC_DAIFMT_CBS_CFM 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  s6_i2s_mod_reg (struct s6000_i2s_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int s6000_i2s_set_dai_fmt(struct snd_soc_dai *cpu_dai,
				   unsigned int fmt)
{
	struct s6000_i2s_dev *dev = cpu_dai->private_data;
	u32 w;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		w = S6_I2S_SCK_IN | S6_I2S_WS_IN;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		w = S6_I2S_SCK_OUT | S6_I2S_WS_IN;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		w = S6_I2S_SCK_IN | S6_I2S_WS_OUT;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		w = S6_I2S_SCK_OUT | S6_I2S_WS_OUT;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		w |= S6_I2S_LEFT_FIRST;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		w |= S6_I2S_RIGHT_FIRST;
		break;
	default:
		return -EINVAL;
	}

	s6_i2s_mod_reg(dev, S6_I2S_INTERFACE_CFG(0),
		       S6_I2S_FIRST | S6_I2S_WS_DIR | S6_I2S_SCK_DIR, w);
	s6_i2s_mod_reg(dev, S6_I2S_INTERFACE_CFG(1),
		       S6_I2S_FIRST | S6_I2S_WS_DIR | S6_I2S_SCK_DIR, w);

	return 0;
}