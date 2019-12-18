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
 int /*<<< orphan*/  ad1981_jacks_blacklist ; 
 scalar_t__ check_list (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * snd_ac97_ad1981x_jack_sense ; 
 int /*<<< orphan*/  snd_ac97_ad198x_2cmic ; 

__attribute__((used)) static int patch_ad1981b_specific(struct snd_ac97 *ac97)
{
	int err;

	if ((err = patch_build_controls(ac97, &snd_ac97_ad198x_2cmic, 1)) < 0)
		return err;
	if (check_list(ac97, ad1981_jacks_blacklist))
		return 0;
	return patch_build_controls(ac97, snd_ac97_ad1981x_jack_sense,
				    ARRAY_SIZE(snd_ac97_ad1981x_jack_sense));
}