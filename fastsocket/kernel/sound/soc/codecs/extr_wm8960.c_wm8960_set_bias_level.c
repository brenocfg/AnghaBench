#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm8960_data {int dres; } ;
struct snd_soc_codec {int bias_level; TYPE_1__* dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {struct wm8960_data* platform_data; } ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8960_APOP1 ; 
 int /*<<< orphan*/  WM8960_APOP2 ; 
 int WM8960_BUFDCOPEN ; 
 int WM8960_BUFIOEN ; 
 int WM8960_DISOP ; 
 int WM8960_POBCTRL ; 
 int /*<<< orphan*/  WM8960_POWER1 ; 
 int WM8960_SOFT_ST ; 
 int WM8960_VREF ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8960_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	struct wm8960_data *pdata = codec->dev->platform_data;
	u16 reg;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* Set VMID to 2x50k */
		reg = snd_soc_read(codec, WM8960_POWER1);
		reg &= ~0x180;
		reg |= 0x80;
		snd_soc_write(codec, WM8960_POWER1, reg);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (codec->bias_level == SND_SOC_BIAS_OFF) {
			/* Enable anti-pop features */
			snd_soc_write(codec, WM8960_APOP1,
				     WM8960_POBCTRL | WM8960_SOFT_ST |
				     WM8960_BUFDCOPEN | WM8960_BUFIOEN);

			/* Discharge HP output */
			reg = WM8960_DISOP;
			if (pdata)
				reg |= pdata->dres << 4;
			snd_soc_write(codec, WM8960_APOP2, reg);

			msleep(400);

			snd_soc_write(codec, WM8960_APOP2, 0);

			/* Enable & ramp VMID at 2x50k */
			reg = snd_soc_read(codec, WM8960_POWER1);
			reg |= 0x80;
			snd_soc_write(codec, WM8960_POWER1, reg);
			msleep(100);

			/* Enable VREF */
			snd_soc_write(codec, WM8960_POWER1, reg | WM8960_VREF);

			/* Disable anti-pop features */
			snd_soc_write(codec, WM8960_APOP1, WM8960_BUFIOEN);
		}

		/* Set VMID to 2x250k */
		reg = snd_soc_read(codec, WM8960_POWER1);
		reg &= ~0x180;
		reg |= 0x100;
		snd_soc_write(codec, WM8960_POWER1, reg);
		break;

	case SND_SOC_BIAS_OFF:
		/* Enable anti-pop features */
		snd_soc_write(codec, WM8960_APOP1,
			     WM8960_POBCTRL | WM8960_SOFT_ST |
			     WM8960_BUFDCOPEN | WM8960_BUFIOEN);

		/* Disable VMID and VREF, let them discharge */
		snd_soc_write(codec, WM8960_POWER1, 0);
		msleep(600);

		snd_soc_write(codec, WM8960_APOP1, 0);
		break;
	}

	codec->bias_level = level;

	return 0;
}