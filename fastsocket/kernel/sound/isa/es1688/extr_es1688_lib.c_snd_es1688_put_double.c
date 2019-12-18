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
struct snd_es1688 {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned char snd_es1688_mixer_read (struct snd_es1688*,int) ; 
 int /*<<< orphan*/  snd_es1688_mixer_write (struct snd_es1688*,int,unsigned char) ; 
 unsigned char snd_es1688_read (struct snd_es1688*,int) ; 
 int /*<<< orphan*/  snd_es1688_write (struct snd_es1688*,int,unsigned char) ; 
 struct snd_es1688* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_es1688_put_double(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int left_reg = kcontrol->private_value & 0xff;
	int right_reg = (kcontrol->private_value >> 8) & 0xff;
	int shift_left = (kcontrol->private_value >> 16) & 0x07;
	int shift_right = (kcontrol->private_value >> 19) & 0x07;
	int mask = (kcontrol->private_value >> 24) & 0xff;
	int invert = (kcontrol->private_value >> 22) & 1;
	int change;
	unsigned char val1, val2, oval1, oval2;
	
	val1 = ucontrol->value.integer.value[0] & mask;
	val2 = ucontrol->value.integer.value[1] & mask;
	if (invert) {
		val1 = mask - val1;
		val2 = mask - val2;
	}
	val1 <<= shift_left;
	val2 <<= shift_right;
	spin_lock_irqsave(&chip->reg_lock, flags);
	if (left_reg != right_reg) {
		if (left_reg < 0xa0)
			oval1 = snd_es1688_mixer_read(chip, left_reg);
		else
			oval1 = snd_es1688_read(chip, left_reg);
		if (right_reg < 0xa0)
			oval2 = snd_es1688_mixer_read(chip, right_reg);
		else
			oval2 = snd_es1688_read(chip, right_reg);
		val1 = (oval1 & ~(mask << shift_left)) | val1;
		val2 = (oval2 & ~(mask << shift_right)) | val2;
		change = val1 != oval1 || val2 != oval2;
		if (change) {
			if (left_reg < 0xa0)
				snd_es1688_mixer_write(chip, left_reg, val1);
			else
				snd_es1688_write(chip, left_reg, val1);
			if (right_reg < 0xa0)
				snd_es1688_mixer_write(chip, right_reg, val1);
			else
				snd_es1688_write(chip, right_reg, val1);
		}
	} else {
		if (left_reg < 0xa0)
			oval1 = snd_es1688_mixer_read(chip, left_reg);
		else
			oval1 = snd_es1688_read(chip, left_reg);
		val1 = (oval1 & ~((mask << shift_left) | (mask << shift_right))) | val1 | val2;
		change = val1 != oval1;
		if (change) {
			if (left_reg < 0xa0)
				snd_es1688_mixer_write(chip, left_reg, val1);
			else
				snd_es1688_write(chip, left_reg, val1);
		}
			
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return change;
}