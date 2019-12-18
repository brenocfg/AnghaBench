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
typedef  int u16 ;
struct snd_soc_codec {int bias_level; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int PWR_CLK_OUT_PDN ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  SSM2602_ACTIVE ; 
 int /*<<< orphan*/  SSM2602_PWR ; 
 int ssm2602_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssm2602_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ssm2602_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	u16 reg = ssm2602_read_reg_cache(codec, SSM2602_PWR) & 0xff7f;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* vref/mid, osc on, dac unmute */
		ssm2602_write(codec, SSM2602_PWR, reg);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* everything off except vref/vmid, */
		ssm2602_write(codec, SSM2602_PWR, reg | PWR_CLK_OUT_PDN);
		break;
	case SND_SOC_BIAS_OFF:
		/* everything off, dac mute, inactive */
		ssm2602_write(codec, SSM2602_ACTIVE, 0);
		ssm2602_write(codec, SSM2602_PWR, 0xffff);
		break;

	}
	codec->bias_level = level;
	return 0;
}