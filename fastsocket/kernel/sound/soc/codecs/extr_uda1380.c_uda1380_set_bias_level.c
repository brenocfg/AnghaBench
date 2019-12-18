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
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int R02_PON_BIAS ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  UDA1380_PM ; 
 int uda1380_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uda1380_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uda1380_set_bias_level(struct snd_soc_codec *codec,
	enum snd_soc_bias_level level)
{
	int pm = uda1380_read_reg_cache(codec, UDA1380_PM);

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		uda1380_write(codec, UDA1380_PM, R02_PON_BIAS | pm);
		break;
	case SND_SOC_BIAS_STANDBY:
		uda1380_write(codec, UDA1380_PM, R02_PON_BIAS);
		break;
	case SND_SOC_BIAS_OFF:
		uda1380_write(codec, UDA1380_PM, 0x0);
		break;
	}
	codec->bias_level = level;
	return 0;
}