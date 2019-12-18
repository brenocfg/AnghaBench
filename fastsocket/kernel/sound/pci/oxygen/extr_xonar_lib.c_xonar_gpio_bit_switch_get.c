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
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int XONAR_GPIO_BIT_INVERT ; 
 int oxygen_read16 (struct oxygen*,int /*<<< orphan*/ ) ; 

int xonar_gpio_bit_switch_get(struct snd_kcontrol *ctl,
			      struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	u16 bit = ctl->private_value;
	bool invert = ctl->private_value & XONAR_GPIO_BIT_INVERT;

	value->value.integer.value[0] =
		!!(oxygen_read16(chip, OXYGEN_GPIO_DATA) & bit) ^ invert;
	return 0;
}