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
struct snd_ac97 {int* rates; int /*<<< orphan*/ * build_ops; int /*<<< orphan*/  ext_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EI_SPDIF ; 
 size_t AC97_RATES_SPDIF ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int SNDRV_PCM_RATE_44100 ; 
 int SNDRV_PCM_RATE_48000 ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  patch_vt1616_ops ; 
 int /*<<< orphan*/ * snd_ac97_controls_vt1617a ; 
 int snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,int) ; 

__attribute__((used)) static int patch_vt1617a(struct snd_ac97 * ac97)
{
	int err = 0;
	int val;

	/* we choose to not fail out at this point, but we tell the
	   caller when we return */

	err = patch_build_controls(ac97, &snd_ac97_controls_vt1617a[0],
				   ARRAY_SIZE(snd_ac97_controls_vt1617a));

	/* bring analog power consumption to normal by turning off the
	 * headphone amplifier, like WinXP driver for EPIA SP
	 */
	/* We need to check the bit before writing it.
	 * On some (many?) hardwares, setting bit actually clears it!
	 */
	val = snd_ac97_read(ac97, 0x5c);
	if (!(val & 0x20))
		snd_ac97_write_cache(ac97, 0x5c, 0x20);

	ac97->ext_id |= AC97_EI_SPDIF;	/* force the detection of spdif */
	ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000;
	ac97->build_ops = &patch_vt1616_ops;

	return err;
}