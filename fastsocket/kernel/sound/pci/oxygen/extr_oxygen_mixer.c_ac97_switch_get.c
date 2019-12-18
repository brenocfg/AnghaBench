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

__attribute__((used)) static int ac97_switch_get(struct snd_kcontrol *ctl,
			   struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	unsigned int codec = (ctl->private_value >> 24) & 1;
	unsigned int index = ctl->private_value & 0xff;
	unsigned int bitnr = (ctl->private_value >> 8) & 0xff;
	int invert = ctl->private_value & (1 << 16);
	u16 reg;

	mutex_lock(&chip->mutex);
	reg = oxygen_read_ac97(chip, codec, index);
	mutex_unlock(&chip->mutex);
	if (!(reg & (1 << bitnr)) ^ !invert)
		value->value.integer.value[0] = 1;
	else
		value->value.integer.value[0] = 0;
	return 0;
}