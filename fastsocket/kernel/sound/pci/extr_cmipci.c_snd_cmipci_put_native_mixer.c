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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {unsigned char* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct cmipci_sb_reg {unsigned char mask; unsigned char left_shift; unsigned char right_shift; scalar_t__ left_reg; scalar_t__ invert; scalar_t__ stereo; } ;
struct cmipci {int /*<<< orphan*/  reg_lock; scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmipci_sb_reg_decode (struct cmipci_sb_reg*,int /*<<< orphan*/ ) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 struct cmipci* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cmipci_put_native_mixer(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	struct cmipci *cm = snd_kcontrol_chip(kcontrol);
	struct cmipci_sb_reg reg;
	unsigned char oreg, nreg, val;

	cmipci_sb_reg_decode(&reg, kcontrol->private_value);
	spin_lock_irq(&cm->reg_lock);
	oreg = inb(cm->iobase + reg.left_reg);
	val = ucontrol->value.integer.value[0] & reg.mask;
	if (reg.invert)
		val = reg.mask - val;
	nreg = oreg & ~(reg.mask << reg.left_shift);
	nreg |= (val << reg.left_shift);
	if (reg.stereo) {
		val = ucontrol->value.integer.value[1] & reg.mask;
		if (reg.invert)
			val = reg.mask - val;
		nreg &= ~(reg.mask << reg.right_shift);
		nreg |= (val << reg.right_shift);
	}
	outb(nreg, cm->iobase + reg.left_reg);
	spin_unlock_irq(&cm->reg_lock);
	return (nreg != oreg);
}