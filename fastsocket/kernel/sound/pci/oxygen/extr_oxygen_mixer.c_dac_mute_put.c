#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* update_dac_mute ) (struct oxygen*) ;} ;
struct oxygen {int dac_mute; int /*<<< orphan*/  mutex; TYPE_3__ model; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct oxygen*) ; 

__attribute__((used)) static int dac_mute_put(struct snd_kcontrol *ctl,
			  struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	int changed;

	mutex_lock(&chip->mutex);
	changed = !value->value.integer.value[0] != chip->dac_mute;
	if (changed) {
		chip->dac_mute = !value->value.integer.value[0];
		chip->model.update_dac_mute(chip);
	}
	mutex_unlock(&chip->mutex);
	return changed;
}