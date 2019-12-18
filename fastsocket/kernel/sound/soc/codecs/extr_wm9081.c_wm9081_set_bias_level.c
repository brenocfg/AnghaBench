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
 int /*<<< orphan*/  WM9081_ANTI_POP_CONTROL ; 
 int /*<<< orphan*/  WM9081_BIAS_CONTROL_1 ; 
 int WM9081_BIAS_ENA ; 
 int WM9081_BIAS_SRC ; 
 int WM9081_LINEOUT_DISCH ; 
 int WM9081_STBY_BIAS_ENA ; 
 int /*<<< orphan*/  WM9081_VMID_CONTROL ; 
 int WM9081_VMID_RAMP ; 
 int WM9081_VMID_SEL_MASK ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm9081_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	u16 reg;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VMID=2*40k */
		reg = snd_soc_read(codec, WM9081_VMID_CONTROL);
		reg &= ~WM9081_VMID_SEL_MASK;
		reg |= 0x2;
		snd_soc_write(codec, WM9081_VMID_CONTROL, reg);

		/* Normal bias current */
		reg = snd_soc_read(codec, WM9081_BIAS_CONTROL_1);
		reg &= ~WM9081_STBY_BIAS_ENA;
		snd_soc_write(codec, WM9081_BIAS_CONTROL_1, reg);
		break;

	case SND_SOC_BIAS_STANDBY:
		/* Initial cold start */
		if (codec->bias_level == SND_SOC_BIAS_OFF) {
			/* Disable LINEOUT discharge */
			reg = snd_soc_read(codec, WM9081_ANTI_POP_CONTROL);
			reg &= ~WM9081_LINEOUT_DISCH;
			snd_soc_write(codec, WM9081_ANTI_POP_CONTROL, reg);

			/* Select startup bias source */
			reg = snd_soc_read(codec, WM9081_BIAS_CONTROL_1);
			reg |= WM9081_BIAS_SRC | WM9081_BIAS_ENA;
			snd_soc_write(codec, WM9081_BIAS_CONTROL_1, reg);

			/* VMID 2*4k; Soft VMID ramp enable */
			reg = snd_soc_read(codec, WM9081_VMID_CONTROL);
			reg |= WM9081_VMID_RAMP | 0x6;
			snd_soc_write(codec, WM9081_VMID_CONTROL, reg);

			mdelay(100);

			/* Normal bias enable & soft start off */
			reg |= WM9081_BIAS_ENA;
			reg &= ~WM9081_VMID_RAMP;
			snd_soc_write(codec, WM9081_VMID_CONTROL, reg);

			/* Standard bias source */
			reg = snd_soc_read(codec, WM9081_BIAS_CONTROL_1);
			reg &= ~WM9081_BIAS_SRC;
			snd_soc_write(codec, WM9081_BIAS_CONTROL_1, reg);
		}

		/* VMID 2*240k */
		reg = snd_soc_read(codec, WM9081_BIAS_CONTROL_1);
		reg &= ~WM9081_VMID_SEL_MASK;
		reg |= 0x40;
		snd_soc_write(codec, WM9081_VMID_CONTROL, reg);

		/* Standby bias current on */
		reg = snd_soc_read(codec, WM9081_BIAS_CONTROL_1);
		reg |= WM9081_STBY_BIAS_ENA;
		snd_soc_write(codec, WM9081_BIAS_CONTROL_1, reg);
		break;

	case SND_SOC_BIAS_OFF:
		/* Startup bias source */
		reg = snd_soc_read(codec, WM9081_BIAS_CONTROL_1);
		reg |= WM9081_BIAS_SRC;
		snd_soc_write(codec, WM9081_BIAS_CONTROL_1, reg);

		/* Disable VMID and biases with soft ramping */
		reg = snd_soc_read(codec, WM9081_VMID_CONTROL);
		reg &= ~(WM9081_VMID_SEL_MASK | WM9081_BIAS_ENA);
		reg |= WM9081_VMID_RAMP;
		snd_soc_write(codec, WM9081_VMID_CONTROL, reg);

		/* Actively discharge LINEOUT */
		reg = snd_soc_read(codec, WM9081_ANTI_POP_CONTROL);
		reg |= WM9081_LINEOUT_DISCH;
		snd_soc_write(codec, WM9081_ANTI_POP_CONTROL, reg);
		break;
	}

	codec->bias_level = level;

	return 0;
}