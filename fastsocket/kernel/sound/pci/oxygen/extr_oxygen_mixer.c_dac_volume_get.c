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
struct TYPE_6__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_4__ {unsigned int dac_channels_mixer; } ;
struct oxygen {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * dac_volume; TYPE_1__ model; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dac_volume_get(struct snd_kcontrol *ctl,
			  struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	unsigned int i;

	mutex_lock(&chip->mutex);
	for (i = 0; i < chip->model.dac_channels_mixer; ++i)
		value->value.integer.value[i] = chip->dac_volume[i];
	mutex_unlock(&chip->mutex);
	return 0;
}