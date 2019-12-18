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
struct tea6330t {unsigned char mleft; unsigned char mright; unsigned char* regs; int /*<<< orphan*/  bus; int /*<<< orphan*/  device; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 size_t TEA6330T_SADDR_VOLUME_LEFT ; 
 size_t TEA6330T_SADDR_VOLUME_RIGHT ; 
 int /*<<< orphan*/  snd_i2c_lock (int /*<<< orphan*/ ) ; 
 int snd_i2c_sendbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_i2c_unlock (int /*<<< orphan*/ ) ; 
 struct tea6330t* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_tea6330t_put_master_volume(struct snd_kcontrol *kcontrol,
					  struct snd_ctl_elem_value *ucontrol)
{
	struct tea6330t *tea = snd_kcontrol_chip(kcontrol);
	int change, count, err;
	unsigned char bytes[3];
	unsigned char val1, val2;
	
	val1 = (ucontrol->value.integer.value[0] % 44) + 0x14;
	val2 = (ucontrol->value.integer.value[1] % 44) + 0x14;
	snd_i2c_lock(tea->bus);
	change = val1 != tea->mleft || val2 != tea->mright;
	tea->mleft = val1;
	tea->mright = val2;
	count = 0;
	if (tea->regs[TEA6330T_SADDR_VOLUME_LEFT] != 0) {
		bytes[count++] = TEA6330T_SADDR_VOLUME_LEFT;
		bytes[count++] = tea->regs[TEA6330T_SADDR_VOLUME_LEFT] = tea->mleft;
	}
	if (tea->regs[TEA6330T_SADDR_VOLUME_RIGHT] != 0) {
		if (count == 0)
			bytes[count++] = TEA6330T_SADDR_VOLUME_RIGHT;
		bytes[count++] = tea->regs[TEA6330T_SADDR_VOLUME_RIGHT] = tea->mright;
	}
	if (count > 0) {
		if ((err = snd_i2c_sendbytes(tea->device, bytes, count)) < 0)
			change = err;
	}
	snd_i2c_unlock(tea->bus);
	return change;
}