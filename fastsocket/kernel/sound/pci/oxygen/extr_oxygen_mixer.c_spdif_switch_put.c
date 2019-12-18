#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {scalar_t__ spdif_playback_enable; int /*<<< orphan*/  mutex; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oxygen_update_spdif_source (struct oxygen*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spdif_switch_put(struct snd_kcontrol *ctl,
			    struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	int changed;

	mutex_lock(&chip->mutex);
	changed = value->value.integer.value[0] != chip->spdif_playback_enable;
	if (changed) {
		chip->spdif_playback_enable = !!value->value.integer.value[0];
		spin_lock_irq(&chip->reg_lock);
		oxygen_update_spdif_source(chip);
		spin_unlock_irq(&chip->reg_lock);
	}
	mutex_unlock(&chip->mutex);
	return changed;
}