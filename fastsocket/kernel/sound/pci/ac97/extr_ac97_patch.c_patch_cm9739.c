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
struct snd_ac97 {int flags; int ext_id; int subsystem_vendor; int subsystem_device; scalar_t__ pci; scalar_t__* rates; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int AC97_CM9739_MULTI_CHAN ; 
 int AC97_CM9739_SPDIF_CTRL ; 
 unsigned short AC97_EA_SPCV ; 
 int AC97_EI_SPDIF ; 
 int AC97_EXTENDED_STATUS ; 
 int AC97_HAS_NO_MASTER_VOL ; 
 int AC97_HAS_NO_PCM_VOL ; 
 int AC97_MASTER ; 
 int AC97_PCM ; 
 size_t AC97_RATES_SPDIF ; 
 scalar_t__ SNDRV_PCM_RATE_48000 ; 
 int /*<<< orphan*/  patch_cm9739_ops ; 
 int snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,int) ; 

__attribute__((used)) static int patch_cm9739(struct snd_ac97 * ac97)
{
	unsigned short val;

	ac97->build_ops = &patch_cm9739_ops;

	/* CM9739/A has no Master and PCM volume although the register reacts */
	ac97->flags |= AC97_HAS_NO_MASTER_VOL | AC97_HAS_NO_PCM_VOL;
	snd_ac97_write_cache(ac97, AC97_MASTER, 0x8000);
	snd_ac97_write_cache(ac97, AC97_PCM, 0x8000);

	/* check spdif */
	val = snd_ac97_read(ac97, AC97_EXTENDED_STATUS);
	if (val & AC97_EA_SPCV) {
		/* enable spdif in */
		snd_ac97_write_cache(ac97, AC97_CM9739_SPDIF_CTRL,
				     snd_ac97_read(ac97, AC97_CM9739_SPDIF_CTRL) | 0x01);
		ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */
	} else {
		ac97->ext_id &= ~AC97_EI_SPDIF; /* disable extended-id */
		ac97->rates[AC97_RATES_SPDIF] = 0;
	}

	/* set-up multi channel */
	/* bit 14: 0 = SPDIF, 1 = EAPD */
	/* bit 13: enable internal vref output for mic */
	/* bit 12: disable center/lfe (swithable) */
	/* bit 10: disable surround/line (switchable) */
	/* bit 9: mix 2 surround off */
	/* bit 4: undocumented; 0 mutes the CM9739A, which defaults to 1 */
	/* bit 3: undocumented; surround? */
	/* bit 0: dB */
	val = snd_ac97_read(ac97, AC97_CM9739_MULTI_CHAN) & (1 << 4);
	val |= (1 << 3);
	val |= (1 << 13);
	if (! (ac97->ext_id & AC97_EI_SPDIF))
		val |= (1 << 14);
	snd_ac97_write_cache(ac97, AC97_CM9739_MULTI_CHAN, val);

	/* FIXME: set up GPIO */
	snd_ac97_write_cache(ac97, 0x70, 0x0100);
	snd_ac97_write_cache(ac97, 0x72, 0x0020);
	/* Special exception for ASUS W1000/CMI9739. It does not have an SPDIF in. */
	if (ac97->pci &&
	     ac97->subsystem_vendor == 0x1043 &&
	     ac97->subsystem_device == 0x1843) {
		snd_ac97_write_cache(ac97, AC97_CM9739_SPDIF_CTRL,
			snd_ac97_read(ac97, AC97_CM9739_SPDIF_CTRL) & ~0x01);
		snd_ac97_write_cache(ac97, AC97_CM9739_MULTI_CHAN,
			snd_ac97_read(ac97, AC97_CM9739_MULTI_CHAN) | (1 << 14));
	}

	return 0;
}