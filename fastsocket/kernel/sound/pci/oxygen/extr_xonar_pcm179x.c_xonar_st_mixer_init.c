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
struct oxygen {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int add_pcm1796_controls (struct oxygen*) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct oxygen*) ; 
 int /*<<< orphan*/ * st_controls ; 

__attribute__((used)) static int xonar_st_mixer_init(struct oxygen *chip)
{
	unsigned int i;
	int err;

	for (i = 0; i < ARRAY_SIZE(st_controls); ++i) {
		err = snd_ctl_add(chip->card,
				  snd_ctl_new1(&st_controls[i], chip));
		if (err < 0)
			return err;
	}
	err = add_pcm1796_controls(chip);
	if (err < 0)
		return err;
	return 0;
}