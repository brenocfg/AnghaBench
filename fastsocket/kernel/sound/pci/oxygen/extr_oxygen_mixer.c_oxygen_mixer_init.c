#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int device_config; int (* mixer_init ) (struct oxygen*) ;} ;
struct oxygen {TYPE_1__ model; scalar_t__ has_ac97_1; scalar_t__ has_ac97_0; } ;
struct TYPE_10__ {int pcm_dev; struct TYPE_10__* controls; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int CAPTURE_1_FROM_SPDIF ; 
 TYPE_2__* ac97_controls ; 
 TYPE_2__* ac97_fp_controls ; 
 int add_controls (struct oxygen*,TYPE_2__*,unsigned int) ; 
 TYPE_2__* controls ; 
 TYPE_2__* monitor_controls ; 
 TYPE_2__* spdif_input_controls ; 
 int stub1 (struct oxygen*) ; 

int oxygen_mixer_init(struct oxygen *chip)
{
	unsigned int i;
	int err;

	err = add_controls(chip, controls, ARRAY_SIZE(controls));
	if (err < 0)
		return err;
	if (chip->model.device_config & CAPTURE_1_FROM_SPDIF) {
		err = add_controls(chip, spdif_input_controls,
				   ARRAY_SIZE(spdif_input_controls));
		if (err < 0)
			return err;
	}
	for (i = 0; i < ARRAY_SIZE(monitor_controls); ++i) {
		if (!(chip->model.device_config & monitor_controls[i].pcm_dev))
			continue;
		err = add_controls(chip, monitor_controls[i].controls,
				   ARRAY_SIZE(monitor_controls[i].controls));
		if (err < 0)
			return err;
	}
	if (chip->has_ac97_0) {
		err = add_controls(chip, ac97_controls,
				   ARRAY_SIZE(ac97_controls));
		if (err < 0)
			return err;
	}
	if (chip->has_ac97_1) {
		err = add_controls(chip, ac97_fp_controls,
				   ARRAY_SIZE(ac97_fp_controls));
		if (err < 0)
			return err;
	}
	return chip->model.mixer_init ? chip->model.mixer_init(chip) : 0;
}