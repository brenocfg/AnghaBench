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
struct snd_soc_codec {int bias_level; } ;
struct snd_soc_card {struct snd_soc_codec* codec; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_DELTA_LATCH2_MODEM_NRESET ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  ams_delta_latch2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ams_delta_set_bias_level(struct snd_soc_card *card,
					enum snd_soc_bias_level level)
{
	struct snd_soc_codec *codec = card->codec;

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
	case SND_SOC_BIAS_STANDBY:
		if (codec->bias_level == SND_SOC_BIAS_OFF)
			ams_delta_latch2_write(AMS_DELTA_LATCH2_MODEM_NRESET,
						AMS_DELTA_LATCH2_MODEM_NRESET);
		break;
	case SND_SOC_BIAS_OFF:
		if (codec->bias_level != SND_SOC_BIAS_OFF)
			ams_delta_latch2_write(AMS_DELTA_LATCH2_MODEM_NRESET,
						0);
	}
	codec->bias_level = level;

	return 0;
}