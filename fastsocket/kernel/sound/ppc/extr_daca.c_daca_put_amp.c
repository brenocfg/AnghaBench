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
struct snd_pmac {struct pmac_daca* mixer_data; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {int* value; } ;
struct TYPE_5__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_4__ {int /*<<< orphan*/  client; } ;
struct pmac_daca {int amp_on; TYPE_1__ i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  DACA_REG_GCFG ; 
 int ENODEV ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int daca_put_amp(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	struct pmac_daca *mix;
	int change;

	if (! (mix = chip->mixer_data))
		return -ENODEV;
	change = mix->amp_on != ucontrol->value.integer.value[0];
	if (change) {
		mix->amp_on = !!ucontrol->value.integer.value[0];
		i2c_smbus_write_byte_data(mix->i2c.client, DACA_REG_GCFG,
					  mix->amp_on ? 0x05 : 0x04);
	}
	return change;
}