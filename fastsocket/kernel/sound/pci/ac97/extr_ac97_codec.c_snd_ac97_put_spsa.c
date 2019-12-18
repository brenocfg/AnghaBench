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
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 unsigned short AC97_EA_SPDIF ; 
 int AC97_EXTENDED_STATUS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned short snd_ac97_read_cache (struct snd_ac97*,int) ; 
 int snd_ac97_update_bits_nolock (struct snd_ac97*,int,unsigned short,unsigned short) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_put_spsa(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int shift = (kcontrol->private_value >> 8) & 0xff;
	int mask = (kcontrol->private_value >> 16) & 0xff;
	// int invert = (kcontrol->private_value >> 24) & 0xff;
	unsigned short value, old, new;
	int change;

	value = (ucontrol->value.integer.value[0] & mask);

	mutex_lock(&ac97->reg_mutex);
	mask <<= shift;
	value <<= shift;
	old = snd_ac97_read_cache(ac97, reg);
	new = (old & ~mask) | value;
	change = old != new;

	if (change) {
		unsigned short extst = snd_ac97_read_cache(ac97, AC97_EXTENDED_STATUS);
		snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0); /* turn off */
		change = snd_ac97_update_bits_nolock(ac97, reg, mask, value);
		if (extst & AC97_EA_SPDIF)
			snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, AC97_EA_SPDIF); /* turn on again */
	}
	mutex_unlock(&ac97->reg_mutex);
	return change;
}