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
 int /*<<< orphan*/  WM8900_REG_ADDCTL ; 
 int WM8900_REG_ADDCTL_BIAS_SRC ; 
 int WM8900_REG_ADDCTL_TEMP_SD ; 
 int WM8900_REG_ADDCTL_VMID_SOFTST ; 
 int /*<<< orphan*/  WM8900_REG_GPIO ; 
 int WM8900_REG_GPIO_TEMP_ENA ; 
 int /*<<< orphan*/  WM8900_REG_HPCTL1 ; 
 int /*<<< orphan*/  WM8900_REG_POWER1 ; 
 int WM8900_REG_POWER1_BIAS_ENA ; 
 int WM8900_REG_POWER1_FLL_ENA ; 
 int WM8900_REG_POWER1_STARTUP_BIAS_ENA ; 
 int /*<<< orphan*/  WM8900_REG_POWER2 ; 
 int WM8900_REG_POWER2_SYSCLK_ENA ; 
 int /*<<< orphan*/  WM8900_REG_POWER3 ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8900_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	u16 reg;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* Enable thermal shutdown */
		reg = snd_soc_read(codec, WM8900_REG_GPIO);
		snd_soc_write(codec, WM8900_REG_GPIO,
			     reg | WM8900_REG_GPIO_TEMP_ENA);
		reg = snd_soc_read(codec, WM8900_REG_ADDCTL);
		snd_soc_write(codec, WM8900_REG_ADDCTL,
			     reg | WM8900_REG_ADDCTL_TEMP_SD);
		break;

	case SND_SOC_BIAS_PREPARE:
		break;

	case SND_SOC_BIAS_STANDBY:
		/* Charge capacitors if initial power up */
		if (codec->bias_level == SND_SOC_BIAS_OFF) {
			/* STARTUP_BIAS_ENA on */
			snd_soc_write(codec, WM8900_REG_POWER1,
				     WM8900_REG_POWER1_STARTUP_BIAS_ENA);

			/* Startup bias mode */
			snd_soc_write(codec, WM8900_REG_ADDCTL,
				     WM8900_REG_ADDCTL_BIAS_SRC |
				     WM8900_REG_ADDCTL_VMID_SOFTST);

			/* VMID 2x50k */
			snd_soc_write(codec, WM8900_REG_POWER1,
				     WM8900_REG_POWER1_STARTUP_BIAS_ENA | 0x1);

			/* Allow capacitors to charge */
			schedule_timeout_interruptible(msecs_to_jiffies(400));

			/* Enable bias */
			snd_soc_write(codec, WM8900_REG_POWER1,
				     WM8900_REG_POWER1_STARTUP_BIAS_ENA |
				     WM8900_REG_POWER1_BIAS_ENA | 0x1);

			snd_soc_write(codec, WM8900_REG_ADDCTL, 0);

			snd_soc_write(codec, WM8900_REG_POWER1,
				     WM8900_REG_POWER1_BIAS_ENA | 0x1);
		}

		reg = snd_soc_read(codec, WM8900_REG_POWER1);
		snd_soc_write(codec, WM8900_REG_POWER1,
			     (reg & WM8900_REG_POWER1_FLL_ENA) |
			     WM8900_REG_POWER1_BIAS_ENA | 0x1);
		snd_soc_write(codec, WM8900_REG_POWER2,
			     WM8900_REG_POWER2_SYSCLK_ENA);
		snd_soc_write(codec, WM8900_REG_POWER3, 0);
		break;

	case SND_SOC_BIAS_OFF:
		/* Startup bias enable */
		reg = snd_soc_read(codec, WM8900_REG_POWER1);
		snd_soc_write(codec, WM8900_REG_POWER1,
			     reg & WM8900_REG_POWER1_STARTUP_BIAS_ENA);
		snd_soc_write(codec, WM8900_REG_ADDCTL,
			     WM8900_REG_ADDCTL_BIAS_SRC |
			     WM8900_REG_ADDCTL_VMID_SOFTST);

		/* Discharge caps */
		snd_soc_write(codec, WM8900_REG_POWER1,
			     WM8900_REG_POWER1_STARTUP_BIAS_ENA);
		schedule_timeout_interruptible(msecs_to_jiffies(500));

		/* Remove clamp */
		snd_soc_write(codec, WM8900_REG_HPCTL1, 0);

		/* Power down */
		snd_soc_write(codec, WM8900_REG_ADDCTL, 0);
		snd_soc_write(codec, WM8900_REG_POWER1, 0);
		snd_soc_write(codec, WM8900_REG_POWER2, 0);
		snd_soc_write(codec, WM8900_REG_POWER3, 0);

		/* Need to let things settle before stopping the clock
		 * to ensure that restart works, see "Stopping the
		 * master clock" in the datasheet. */
		schedule_timeout_interruptible(msecs_to_jiffies(1));
		snd_soc_write(codec, WM8900_REG_POWER2,
			     WM8900_REG_POWER2_SYSCLK_ENA);
		break;
	}
	codec->bias_level = level;
	return 0;
}