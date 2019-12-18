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
struct TYPE_2__ {scalar_t__ dev_flags; } ;
struct snd_ac97 {int /*<<< orphan*/  flags; TYPE_1__ spec; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int AC97_ALC650_LFE_DAC_VOL ; 
 int AC97_ALC650_MULTICH ; 
 int AC97_ALC650_SURR_DAC_VOL ; 
 int /*<<< orphan*/  AC97_HAS_8CH ; 
 int /*<<< orphan*/  AC97_INT_PAGING ; 
 int /*<<< orphan*/  AC97_PAGE_MASK ; 
 int /*<<< orphan*/  AC97_PAGE_VENDOR ; 
 int /*<<< orphan*/  patch_alc850_ops ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,int) ; 

__attribute__((used)) static int patch_alc850(struct snd_ac97 *ac97)
{
	ac97->build_ops = &patch_alc850_ops;

	ac97->spec.dev_flags = 0; /* for IEC958 playback route - ALC655 compatible */
	ac97->flags |= AC97_HAS_8CH;

	/* assume only page 0 for writing cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOR);

	/* adjust default values */
	/* set default: spdif-in enabled,
	   spdif-in monitor off, spdif-in PCM off
	   center on mic off, surround on line-in off
	   duplicate front off
	   NB default bit 10=0 = Aux is Capture, not Back Surround
	*/
	snd_ac97_write_cache(ac97, AC97_ALC650_MULTICH, 1<<15);
	/* SURR_OUT: on, Surr 1kOhm: on, Surr Amp: off, Front 1kOhm: off
	 * Front Amp: on, Vref: enable, Center 1kOhm: on, Mix: on
	 */
	snd_ac97_write_cache(ac97, 0x7a, (1<<1)|(1<<4)|(0<<5)|(1<<6)|
			     (1<<7)|(0<<12)|(1<<13)|(0<<14));
	/* detection UIO2,3: all path floating, UIO3: MIC, Vref2: disable,
	 * UIO1: FRONT, Vref3: disable, UIO3: LINE, Front-Mic: mute
	 */
	snd_ac97_write_cache(ac97, 0x76, (0<<0)|(0<<2)|(1<<4)|(1<<7)|(2<<8)|
			     (1<<11)|(0<<12)|(1<<15));

	/* full DAC volume */
	snd_ac97_write_cache(ac97, AC97_ALC650_SURR_DAC_VOL, 0x0808);
	snd_ac97_write_cache(ac97, AC97_ALC650_LFE_DAC_VOL, 0x0808);
	return 0;
}