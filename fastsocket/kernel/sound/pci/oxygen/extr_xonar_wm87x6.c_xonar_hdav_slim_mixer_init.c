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
struct snd_kcontrol {int dummy; } ;
struct oxygen {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int add_lc_controls (struct oxygen*) ; 
 int /*<<< orphan*/ * hdav_slim_controls ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct oxygen*) ; 

__attribute__((used)) static int xonar_hdav_slim_mixer_init(struct oxygen *chip)
{
	unsigned int i;
	struct snd_kcontrol *ctl;
	int err;

	for (i = 0; i < ARRAY_SIZE(hdav_slim_controls); ++i) {
		ctl = snd_ctl_new1(&hdav_slim_controls[i], chip);
		if (!ctl)
			return -ENOMEM;
		err = snd_ctl_add(chip->card, ctl);
		if (err < 0)
			return err;
	}

	return add_lc_controls(chip);
}