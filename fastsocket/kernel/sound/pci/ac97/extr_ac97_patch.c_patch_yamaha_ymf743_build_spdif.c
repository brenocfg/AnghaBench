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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_YMF7X3_DIT_CTRL ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * snd_ac97_controls_spdif ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * snd_ac97_yamaha_ymf743_controls_spdif ; 

__attribute__((used)) static int patch_yamaha_ymf743_build_spdif(struct snd_ac97 *ac97)
{
	int err;

	err = patch_build_controls(ac97, &snd_ac97_controls_spdif[0], 3);
	if (err < 0)
		return err;
	err = patch_build_controls(ac97,
				   snd_ac97_yamaha_ymf743_controls_spdif, 3);
	if (err < 0)
		return err;
	/* set default PCM S/PDIF params */
	/* PCM audio,no copyright,no preemphasis,PCM coder,original */
	snd_ac97_write_cache(ac97, AC97_YMF7X3_DIT_CTRL, 0xa201);
	return 0;
}