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
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct generic_data* model_data; } ;
struct generic_data {unsigned int* wm8785_regs; } ;

/* Variables and functions */
 unsigned int WM8785_HPFL ; 
 unsigned int WM8785_HPFR ; 
 size_t WM8785_R2 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm8785_write (struct oxygen*,size_t,unsigned int) ; 

__attribute__((used)) static int hpf_put(struct snd_kcontrol *ctl, struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct generic_data *data = chip->model_data;
	unsigned int reg;
	int changed;

	mutex_lock(&chip->mutex);
	reg = data->wm8785_regs[WM8785_R2] & ~(WM8785_HPFR | WM8785_HPFL);
	if (value->value.enumerated.item[0])
		reg |= WM8785_HPFR | WM8785_HPFL;
	changed = reg != data->wm8785_regs[WM8785_R2];
	if (changed)
		wm8785_write(chip, WM8785_R2, reg);
	mutex_unlock(&chip->mutex);
	return changed;
}