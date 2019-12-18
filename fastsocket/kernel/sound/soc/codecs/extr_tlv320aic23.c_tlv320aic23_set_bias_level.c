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
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  TLV320AIC23_ACTIVE ; 
 int /*<<< orphan*/  TLV320AIC23_PWR ; 
 int tlv320aic23_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlv320aic23_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tlv320aic23_set_bias_level(struct snd_soc_codec *codec,
				      enum snd_soc_bias_level level)
{
	u16 reg = tlv320aic23_read_reg_cache(codec, TLV320AIC23_PWR) & 0xff7f;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* vref/mid, osc on, dac unmute */
		tlv320aic23_write(codec, TLV320AIC23_PWR, reg);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/* everything off except vref/vmid, */
		tlv320aic23_write(codec, TLV320AIC23_PWR, reg | 0x0040);
		break;
	case SND_SOC_BIAS_OFF:
		/* everything off, dac mute, inactive */
		tlv320aic23_write(codec, TLV320AIC23_ACTIVE, 0x0);
		tlv320aic23_write(codec, TLV320AIC23_PWR, 0xffff);
		break;
	}
	codec->bias_level = level;
	return 0;
}