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
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {int* saved; } ;
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; TYPE_3__ gpio; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_DEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spi_write (struct snd_ice1712*,int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static int cs_source_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned char val;
	int change = 0;

	mutex_lock(&ice->gpio_mutex);
	if (ucontrol->value.enumerated.item[0] != ice->gpio.saved[0]) {
		ice->gpio.saved[0] = ucontrol->value.enumerated.item[0] & 3;
		val = 0x80 | (ice->gpio.saved[0] << 3);
		spi_write(ice, CS_DEV, 0x04, val);
		change = 1;
	}
	mutex_unlock(&ice->gpio_mutex);
	return change;
}