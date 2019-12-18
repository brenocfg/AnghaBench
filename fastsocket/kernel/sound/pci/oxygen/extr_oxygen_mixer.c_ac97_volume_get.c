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
typedef  int u16 ;
struct snd_kcontrol {int private_value; struct oxygen* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int oxygen_read_ac97 (struct oxygen*,unsigned int,unsigned int) ; 

__attribute__((used)) static int ac97_volume_get(struct snd_kcontrol *ctl,
			   struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	unsigned int codec = (ctl->private_value >> 24) & 1;
	int stereo = (ctl->private_value >> 16) & 1;
	unsigned int index = ctl->private_value & 0xff;
	u16 reg;

	mutex_lock(&chip->mutex);
	reg = oxygen_read_ac97(chip, codec, index);
	mutex_unlock(&chip->mutex);
	if (!stereo) {
		value->value.integer.value[0] = 31 - (reg & 0x1f);
	} else {
		value->value.integer.value[0] = 31 - ((reg >> 8) & 0x1f);
		value->value.integer.value[1] = 31 - (reg & 0x1f);
	}
	return 0;
}