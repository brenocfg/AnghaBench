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
 int /*<<< orphan*/  WM8961_ANTI_POP ; 
 int WM8961_BUFDCOPEN ; 
 int WM8961_BUFIOEN ; 
 int /*<<< orphan*/  WM8961_PWR_MGMT_1 ; 
 int WM8961_VMIDSEL_MASK ; 
 int WM8961_VMIDSEL_SHIFT ; 
 int WM8961_VREF ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8961_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	u16 reg;

	/* This is all slightly unusual since we have no bypass paths
	 * and the output amplifier structure means we can just slam
	 * the biases straight up rather than having to ramp them
	 * slowly.
	 */
	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		if (codec->bias_level == SND_SOC_BIAS_STANDBY) {
			/* Enable bias generation */
			reg = snd_soc_read(codec, WM8961_ANTI_POP);
			reg |= WM8961_BUFIOEN | WM8961_BUFDCOPEN;
			snd_soc_write(codec, WM8961_ANTI_POP, reg);

			/* VMID=2*50k, VREF */
			reg = snd_soc_read(codec, WM8961_PWR_MGMT_1);
			reg &= ~WM8961_VMIDSEL_MASK;
			reg |= (1 << WM8961_VMIDSEL_SHIFT) | WM8961_VREF;
			snd_soc_write(codec, WM8961_PWR_MGMT_1, reg);
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		if (codec->bias_level == SND_SOC_BIAS_PREPARE) {
			/* VREF off */
			reg = snd_soc_read(codec, WM8961_PWR_MGMT_1);
			reg &= ~WM8961_VREF;
			snd_soc_write(codec, WM8961_PWR_MGMT_1, reg);

			/* Bias generation off */
			reg = snd_soc_read(codec, WM8961_ANTI_POP);
			reg &= ~(WM8961_BUFIOEN | WM8961_BUFDCOPEN);
			snd_soc_write(codec, WM8961_ANTI_POP, reg);

			/* VMID off */
			reg = snd_soc_read(codec, WM8961_PWR_MGMT_1);
			reg &= ~WM8961_VMIDSEL_MASK;
			snd_soc_write(codec, WM8961_PWR_MGMT_1, reg);
		}
		break;

	case SND_SOC_BIAS_OFF:
		break;
	}

	codec->bias_level = level;

	return 0;
}