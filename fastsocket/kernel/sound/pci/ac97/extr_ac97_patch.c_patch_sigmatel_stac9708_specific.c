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
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ *,int) ; 
 int patch_sigmatel_stac97xx_specific (struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_ac97_remove_ctl (struct snd_ac97*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ac97_rename_vol_ctl (struct snd_ac97*,char*,char*) ; 
 int /*<<< orphan*/  snd_ac97_stac9708_bias_control ; 

__attribute__((used)) static int patch_sigmatel_stac9708_specific(struct snd_ac97 *ac97)
{
	int err;

	/* the register bit is writable, but the function is not implemented: */
	snd_ac97_remove_ctl(ac97, "PCM Out Path & Mute", NULL);

	snd_ac97_rename_vol_ctl(ac97, "Headphone Playback", "Sigmatel Surround Playback");
	if ((err = patch_build_controls(ac97, &snd_ac97_stac9708_bias_control, 1)) < 0)
		return err;
	return patch_sigmatel_stac97xx_specific(ac97);
}