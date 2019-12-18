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
 int /*<<< orphan*/  WM8580_ADC_CONTROL1 ; 
 int /*<<< orphan*/  WM8580_PWRDN1 ; 
 int WM8580_PWRDN1_ALLDACPD ; 
 int WM8580_PWRDN1_PWDN ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8580_set_bias_level(struct snd_soc_codec *codec,
	enum snd_soc_bias_level level)
{
	u16 reg;
	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		break;

	case SND_SOC_BIAS_STANDBY:
		if (codec->bias_level == SND_SOC_BIAS_OFF) {
			/* Power up and get individual control of the DACs */
			reg = snd_soc_read(codec, WM8580_PWRDN1);
			reg &= ~(WM8580_PWRDN1_PWDN | WM8580_PWRDN1_ALLDACPD);
			snd_soc_write(codec, WM8580_PWRDN1, reg);

			/* Make VMID high impedence */
			reg = snd_soc_read(codec,  WM8580_ADC_CONTROL1);
			reg &= ~0x100;
			snd_soc_write(codec, WM8580_ADC_CONTROL1, reg);
		}
		break;

	case SND_SOC_BIAS_OFF:
		reg = snd_soc_read(codec, WM8580_PWRDN1);
		snd_soc_write(codec, WM8580_PWRDN1, reg | WM8580_PWRDN1_PWDN);
		break;
	}
	codec->bias_level = level;
	return 0;
}