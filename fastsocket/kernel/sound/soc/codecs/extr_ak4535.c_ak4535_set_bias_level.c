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
struct snd_soc_codec {int bias_level; int /*<<< orphan*/  dai; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  AK4535_PM1 ; 
 int /*<<< orphan*/  AK4535_PM2 ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  ak4535_mute (int /*<<< orphan*/ ,int) ; 
 int ak4535_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ak4535_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ak4535_set_bias_level(struct snd_soc_codec *codec,
	enum snd_soc_bias_level level)
{
	u16 i;

	switch (level) {
	case SND_SOC_BIAS_ON:
		ak4535_mute(codec->dai, 0);
		break;
	case SND_SOC_BIAS_PREPARE:
		ak4535_mute(codec->dai, 1);
		break;
	case SND_SOC_BIAS_STANDBY:
		i = ak4535_read_reg_cache(codec, AK4535_PM1);
		ak4535_write(codec, AK4535_PM1, i | 0x80);
		i = ak4535_read_reg_cache(codec, AK4535_PM2);
		ak4535_write(codec, AK4535_PM2, i & (~0x80));
		break;
	case SND_SOC_BIAS_OFF:
		i = ak4535_read_reg_cache(codec, AK4535_PM1);
		ak4535_write(codec, AK4535_PM1, i & (~0x80));
		break;
	}
	codec->bias_level = level;
	return 0;
}