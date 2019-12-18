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
struct snd_ac97 {int power_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ac97_page_restore (struct snd_ac97*,int) ; 
 int snd_ac97_page_save (struct snd_ac97*,int,struct snd_kcontrol*) ; 
 int snd_ac97_update_bits (struct snd_ac97*,int,unsigned short,unsigned short) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  update_power_regs (struct snd_ac97*) ; 

__attribute__((used)) static int snd_ac97_put_volsw(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int shift = (kcontrol->private_value >> 8) & 0x0f;
	int rshift = (kcontrol->private_value >> 12) & 0x0f;
	int mask = (kcontrol->private_value >> 16) & 0xff;
	int invert = (kcontrol->private_value >> 24) & 0x01;
	int err, page_save;
	unsigned short val, val2, val_mask;
	
	page_save = snd_ac97_page_save(ac97, reg, kcontrol);
	val = (ucontrol->value.integer.value[0] & mask);
	if (invert)
		val = mask - val;
	val_mask = mask << shift;
	val = val << shift;
	if (shift != rshift) {
		val2 = (ucontrol->value.integer.value[1] & mask);
		if (invert)
			val2 = mask - val2;
		val_mask |= mask << rshift;
		val |= val2 << rshift;
	}
	err = snd_ac97_update_bits(ac97, reg, val_mask, val);
	snd_ac97_page_restore(ac97, page_save);
#ifdef CONFIG_SND_AC97_POWER_SAVE
	/* check analog mixer power-down */
	if ((val_mask & 0x8000) &&
	    (kcontrol->private_value & (1<<30))) {
		if (val & 0x8000)
			ac97->power_up &= ~(1 << (reg>>1));
		else
			ac97->power_up |= 1 << (reg>>1);
		update_power_regs(ac97);
	}
#endif
	return err;
}