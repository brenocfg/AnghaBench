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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * snd_ac97_ad1985_controls ; 
 int /*<<< orphan*/  snd_ac97_ad198x_2cmic ; 
 int /*<<< orphan*/  snd_ac97_rename_vol_ctl (struct snd_ac97*,char*,char*) ; 

__attribute__((used)) static int patch_ad1985_specific(struct snd_ac97 *ac97)
{
	int err;

	/* rename 0x04 as "Master" and 0x02 as "Master Surround" */
	snd_ac97_rename_vol_ctl(ac97, "Master Playback",
				"Master Surround Playback");
	snd_ac97_rename_vol_ctl(ac97, "Headphone Playback", "Master Playback");

	if ((err = patch_build_controls(ac97, &snd_ac97_ad198x_2cmic, 1)) < 0)
		return err;

	return patch_build_controls(ac97, snd_ac97_ad1985_controls,
				    ARRAY_SIZE(snd_ac97_ad1985_controls));
}