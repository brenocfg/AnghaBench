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
struct TYPE_2__ {int /*<<< orphan*/  lineout2_diff; int /*<<< orphan*/  lineout1_diff; } ;
struct wm8993_priv {TYPE_1__ pdata; } ;
struct snd_soc_codec {int bias_level; struct wm8993_priv* private_data; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8993_ANTIPOP1 ; 
 int /*<<< orphan*/  WM8993_ANTIPOP2 ; 
 int WM8993_BIAS_ENA ; 
 int WM8993_BIAS_SRC ; 
 int WM8993_LINEOUT_VMID_BUF_ENA ; 
 int /*<<< orphan*/  WM8993_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  WM8993_POWER_MANAGEMENT_2 ; 
 int WM8993_STARTUP_BIAS_ENA ; 
 int WM8993_TSHUT_ENA ; 
 int WM8993_VMID_BUF_ENA ; 
 int WM8993_VMID_RAMP_MASK ; 
 int WM8993_VMID_SEL_MASK ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_soc_update_bits (struct snd_soc_codec*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8993_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	struct wm8993_priv *wm8993 = codec->private_data;

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		/* VMID=2*40k */
		snd_soc_update_bits(codec, WM8993_POWER_MANAGEMENT_1,
				    WM8993_VMID_SEL_MASK, 0x2);
		snd_soc_update_bits(codec, WM8993_POWER_MANAGEMENT_2,
				    WM8993_TSHUT_ENA, WM8993_TSHUT_ENA);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (codec->bias_level == SND_SOC_BIAS_OFF) {
			/* Bring up VMID with fast soft start */
			snd_soc_update_bits(codec, WM8993_ANTIPOP2,
					    WM8993_STARTUP_BIAS_ENA |
					    WM8993_VMID_BUF_ENA |
					    WM8993_VMID_RAMP_MASK |
					    WM8993_BIAS_SRC,
					    WM8993_STARTUP_BIAS_ENA |
					    WM8993_VMID_BUF_ENA |
					    WM8993_VMID_RAMP_MASK |
					    WM8993_BIAS_SRC);

			/* If either line output is single ended we
			 * need the VMID buffer */
			if (!wm8993->pdata.lineout1_diff ||
			    !wm8993->pdata.lineout2_diff)
				snd_soc_update_bits(codec, WM8993_ANTIPOP1,
						 WM8993_LINEOUT_VMID_BUF_ENA,
						 WM8993_LINEOUT_VMID_BUF_ENA);

			/* VMID=2*40k */
			snd_soc_update_bits(codec, WM8993_POWER_MANAGEMENT_1,
					    WM8993_VMID_SEL_MASK |
					    WM8993_BIAS_ENA,
					    WM8993_BIAS_ENA | 0x2);
			msleep(32);

			/* Switch to normal bias */
			snd_soc_update_bits(codec, WM8993_ANTIPOP2,
					    WM8993_BIAS_SRC |
					    WM8993_STARTUP_BIAS_ENA, 0);
		}

		/* VMID=2*240k */
		snd_soc_update_bits(codec, WM8993_POWER_MANAGEMENT_1,
				    WM8993_VMID_SEL_MASK, 0x4);

		snd_soc_update_bits(codec, WM8993_POWER_MANAGEMENT_2,
				    WM8993_TSHUT_ENA, 0);
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_update_bits(codec, WM8993_ANTIPOP1,
				    WM8993_LINEOUT_VMID_BUF_ENA, 0);

		snd_soc_update_bits(codec, WM8993_POWER_MANAGEMENT_1,
				    WM8993_VMID_SEL_MASK | WM8993_BIAS_ENA,
				    0);
		break;
	}

	codec->bias_level = level;

	return 0;
}