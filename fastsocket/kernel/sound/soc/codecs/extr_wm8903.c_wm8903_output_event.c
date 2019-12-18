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
struct snd_soc_dapm_widget {int reg; int shift; struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int SND_SOC_DAPM_POST_PMU ; 
 int SND_SOC_DAPM_PRE_PMD ; 
 int SND_SOC_DAPM_PRE_PMU ; 
 int WM8903_ANALOGUE_HP_0 ; 
 int WM8903_ANALOGUE_LINEOUT_0 ; 
 int WM8903_DC_SERVO_0 ; 
 int WM8903_OUTPUT_IN ; 
 int WM8903_OUTPUT_INT ; 
 int WM8903_OUTPUT_OUT ; 
 int WM8903_OUTPUT_SHORT ; 
#define  WM8903_POWER_MANAGEMENT_2 129 
#define  WM8903_POWER_MANAGEMENT_3 128 
 int snd_soc_read (struct snd_soc_codec*,int) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int,int) ; 

__attribute__((used)) static int wm8903_output_event(struct snd_soc_dapm_widget *w,
			       struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	u16 val;
	u16 reg;
	u16 dcs_reg;
	u16 dcs_bit;
	int shift;

	switch (w->reg) {
	case WM8903_POWER_MANAGEMENT_2:
		reg = WM8903_ANALOGUE_HP_0;
		dcs_bit = 0 + w->shift;
		break;
	case WM8903_POWER_MANAGEMENT_3:
		reg = WM8903_ANALOGUE_LINEOUT_0;
		dcs_bit = 2 + w->shift;
		break;
	default:
		BUG();
		return -EINVAL;  /* Spurious warning from some compilers */
	}

	switch (w->shift) {
	case 0:
		shift = 0;
		break;
	case 1:
		shift = 4;
		break;
	default:
		BUG();
		return -EINVAL;  /* Spurious warning from some compilers */
	}

	if (event & SND_SOC_DAPM_PRE_PMU) {
		val = snd_soc_read(codec, reg);

		/* Short the output */
		val &= ~(WM8903_OUTPUT_SHORT << shift);
		snd_soc_write(codec, reg, val);
	}

	if (event & SND_SOC_DAPM_POST_PMU) {
		val = snd_soc_read(codec, reg);

		val |= (WM8903_OUTPUT_IN << shift);
		snd_soc_write(codec, reg, val);

		val |= (WM8903_OUTPUT_INT << shift);
		snd_soc_write(codec, reg, val);

		/* Turn on the output ENA_OUTP */
		val |= (WM8903_OUTPUT_OUT << shift);
		snd_soc_write(codec, reg, val);

		/* Enable the DC servo */
		dcs_reg = snd_soc_read(codec, WM8903_DC_SERVO_0);
		dcs_reg |= dcs_bit;
		snd_soc_write(codec, WM8903_DC_SERVO_0, dcs_reg);

		/* Remove the short */
		val |= (WM8903_OUTPUT_SHORT << shift);
		snd_soc_write(codec, reg, val);
	}

	if (event & SND_SOC_DAPM_PRE_PMD) {
		val = snd_soc_read(codec, reg);

		/* Short the output */
		val &= ~(WM8903_OUTPUT_SHORT << shift);
		snd_soc_write(codec, reg, val);

		/* Disable the DC servo */
		dcs_reg = snd_soc_read(codec, WM8903_DC_SERVO_0);
		dcs_reg &= ~dcs_bit;
		snd_soc_write(codec, WM8903_DC_SERVO_0, dcs_reg);

		/* Then disable the intermediate and output stages */
		val &= ~((WM8903_OUTPUT_OUT | WM8903_OUTPUT_INT |
			  WM8903_OUTPUT_IN) << shift);
		snd_soc_write(codec, reg, val);
	}

	return 0;
}