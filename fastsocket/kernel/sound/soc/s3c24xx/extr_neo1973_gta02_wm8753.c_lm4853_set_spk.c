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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTA02_GPIO_HP_IN ; 
 int /*<<< orphan*/  LM4853_SPK ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lm4853_state ; 

__attribute__((used)) static int lm4853_set_spk(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	int val = ucontrol->value.integer.value[0];

	if (val) {
		lm4853_state |= LM4853_SPK;
		gpio_set_value(GTA02_GPIO_HP_IN, 0);
	} else {
		lm4853_state &= ~LM4853_SPK;
		gpio_set_value(GTA02_GPIO_HP_IN, 1);
	}

	return 0;
}