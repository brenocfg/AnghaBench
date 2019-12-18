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
struct TYPE_2__ {int dev_flags; } ;
struct snd_ac97 {int id; int subsystem_vendor; int subsystem_device; TYPE_1__ spec; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_ALC650_CLOCK ; 
 int /*<<< orphan*/  AC97_ALC650_GPIO_SETUP ; 
 int /*<<< orphan*/  AC97_ALC650_GPIO_STATUS ; 
 int /*<<< orphan*/  AC97_ALC650_LFE_DAC_VOL ; 
 int /*<<< orphan*/  AC97_ALC650_MULTICH ; 
 int /*<<< orphan*/  AC97_ALC650_REVISION ; 
 int /*<<< orphan*/  AC97_ALC650_SURR_DAC_VOL ; 
 int /*<<< orphan*/  patch_alc650_ops ; 
 int snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int patch_alc650(struct snd_ac97 * ac97)
{
	unsigned short val;

	ac97->build_ops = &patch_alc650_ops;

	/* determine the revision */
	val = snd_ac97_read(ac97, AC97_ALC650_REVISION) & 0x3f;
	if (val < 3)
		ac97->id = 0x414c4720;          /* Old version */
	else if (val < 0x10)
		ac97->id = 0x414c4721;          /* D version */
	else if (val < 0x20)
		ac97->id = 0x414c4722;          /* E version */
	else if (val < 0x30)
		ac97->id = 0x414c4723;          /* F version */

	/* revision E or F */
	/* FIXME: what about revision D ? */
	ac97->spec.dev_flags = (ac97->id == 0x414c4722 ||
				ac97->id == 0x414c4723);

	/* enable AC97_ALC650_GPIO_SETUP, AC97_ALC650_CLOCK for R/W */
	snd_ac97_write_cache(ac97, AC97_ALC650_GPIO_STATUS, 
		snd_ac97_read(ac97, AC97_ALC650_GPIO_STATUS) | 0x8000);

	/* Enable SPDIF-IN only on Rev.E and above */
	val = snd_ac97_read(ac97, AC97_ALC650_CLOCK);
	/* SPDIF IN with pin 47 */
	if (ac97->spec.dev_flags &&
	    /* ASUS A6KM requires EAPD */
	    ! (ac97->subsystem_vendor == 0x1043 &&
	       ac97->subsystem_device == 0x1103))
		val |= 0x03; /* enable */
	else
		val &= ~0x03; /* disable */
	snd_ac97_write_cache(ac97, AC97_ALC650_CLOCK, val);

	/* set default: slot 3,4,7,8,6,9
	   spdif-in monitor off, analog-spdif off, spdif-in off
	   center on mic off, surround on line-in off
	   downmix off, duplicate front off
	*/
	snd_ac97_write_cache(ac97, AC97_ALC650_MULTICH, 0);

	/* set GPIO0 for mic bias */
	/* GPIO0 pin output, no interrupt, high */
	snd_ac97_write_cache(ac97, AC97_ALC650_GPIO_SETUP,
			     snd_ac97_read(ac97, AC97_ALC650_GPIO_SETUP) | 0x01);
	snd_ac97_write_cache(ac97, AC97_ALC650_GPIO_STATUS,
			     (snd_ac97_read(ac97, AC97_ALC650_GPIO_STATUS) | 0x100) & ~0x10);

	/* full DAC volume */
	snd_ac97_write_cache(ac97, AC97_ALC650_SURR_DAC_VOL, 0x0808);
	snd_ac97_write_cache(ac97, AC97_ALC650_LFE_DAC_VOL, 0x0808);
	return 0;
}