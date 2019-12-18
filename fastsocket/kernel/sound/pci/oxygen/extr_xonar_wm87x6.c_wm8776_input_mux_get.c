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
struct xonar_wm87x6 {unsigned int* wm8776_regs; } ;
struct snd_kcontrol {unsigned int private_value; struct oxygen* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 size_t WM8776_ADCMUX ; 

__attribute__((used)) static int wm8776_input_mux_get(struct snd_kcontrol *ctl,
				struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_wm87x6 *data = chip->model_data;
	unsigned int mux_bit = ctl->private_value;

	value->value.integer.value[0] =
		!!(data->wm8776_regs[WM8776_ADCMUX] & mux_bit);
	return 0;
}