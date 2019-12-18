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
struct soc_enum {scalar_t__ shift_l; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  codec; TYPE_1__* kcontrols; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {scalar_t__ private_value; } ;

/* Variables and functions */
 unsigned char TWL4030_MICBIAS1_CTL ; 
 unsigned char TWL4030_MICBIAS2_CTL ; 
 int /*<<< orphan*/  TWL4030_REG_ADCMICSEL ; 
 int /*<<< orphan*/  TWL4030_REG_MICBIAS_CTL ; 
 unsigned char TWL4030_TX1IN_SEL ; 
 unsigned char TWL4030_TX2IN_SEL ; 
 unsigned char twl4030_read_reg_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int micpath_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct soc_enum *e = (struct soc_enum *)w->kcontrols->private_value;
	unsigned char adcmicsel, micbias_ctl;

	adcmicsel = twl4030_read_reg_cache(w->codec, TWL4030_REG_ADCMICSEL);
	micbias_ctl = twl4030_read_reg_cache(w->codec, TWL4030_REG_MICBIAS_CTL);
	/* Prepare the bits for the given TX path:
	 * shift_l == 0: TX1 microphone path
	 * shift_l == 2: TX2 microphone path */
	if (e->shift_l) {
		/* TX2 microphone path */
		if (adcmicsel & TWL4030_TX2IN_SEL)
			micbias_ctl |= TWL4030_MICBIAS2_CTL; /* digimic */
		else
			micbias_ctl &= ~TWL4030_MICBIAS2_CTL;
	} else {
		/* TX1 microphone path */
		if (adcmicsel & TWL4030_TX1IN_SEL)
			micbias_ctl |= TWL4030_MICBIAS1_CTL; /* digimic */
		else
			micbias_ctl &= ~TWL4030_MICBIAS1_CTL;
	}

	twl4030_write(w->codec, TWL4030_REG_MICBIAS_CTL, micbias_ctl);

	return 0;
}