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
struct snd_usb_midi {int /*<<< orphan*/  mutex; } ;
struct snd_kcontrol {int private_value; struct snd_usb_midi* private_data; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int roland_load_put(struct snd_kcontrol *kcontrol,
			   struct snd_ctl_elem_value *value)
{
	struct snd_usb_midi* umidi = kcontrol->private_data;
	int changed;

	if (value->value.enumerated.item[0] > 1)
		return -EINVAL;
	mutex_lock(&umidi->mutex);
	changed = value->value.enumerated.item[0] != kcontrol->private_value;
	if (changed)
		kcontrol->private_value = value->value.enumerated.item[0];
	mutex_unlock(&umidi->mutex);
	return changed;
}