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
struct xonar_wm87x6 {int* wm8776_regs; } ;
struct snd_kcontrol {int private_value; struct oxygen* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm8776_write (struct oxygen*,unsigned int,int) ; 

__attribute__((used)) static int wm8776_bit_switch_put(struct snd_kcontrol *ctl,
				 struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_wm87x6 *data = chip->model_data;
	u16 bit = ctl->private_value & 0xffff;
	u16 reg_value;
	unsigned int reg_index = (ctl->private_value >> 16) & 0xff;
	bool invert = (ctl->private_value >> 24) & 1;
	int changed;

	mutex_lock(&chip->mutex);
	reg_value = data->wm8776_regs[reg_index] & ~bit;
	if (value->value.integer.value[0] ^ invert)
		reg_value |= bit;
	changed = reg_value != data->wm8776_regs[reg_index];
	if (changed)
		wm8776_write(chip, reg_index, reg_value);
	mutex_unlock(&chip->mutex);
	return changed;
}