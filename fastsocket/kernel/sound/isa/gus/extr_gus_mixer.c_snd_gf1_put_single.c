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
struct snd_kcontrol {int private_value; } ;
struct TYPE_6__ {unsigned char active_voice; } ;
struct snd_gus_card {unsigned char mix_cntrl_reg; int /*<<< orphan*/  reg_lock; TYPE_3__ gf1; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  GF1PAGE ; 
 int /*<<< orphan*/  GUSP (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIXCNTRLREG ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 struct snd_gus_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_gf1_put_single(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int shift = kcontrol->private_value & 0xff;
	int invert = (kcontrol->private_value >> 8) & 1;
	int change;
	unsigned char oval, nval;
	
	nval = ucontrol->value.integer.value[0] & 1;
	if (invert)
		nval ^= 1;
	nval <<= shift;
	spin_lock_irqsave(&gus->reg_lock, flags);
	oval = gus->mix_cntrl_reg;
	nval = (oval & ~(1 << shift)) | nval;
	change = nval != oval;
	outb(gus->mix_cntrl_reg = nval, GUSP(gus, MIXCNTRLREG));
	outb(gus->gf1.active_voice = 0, GUSP(gus, GF1PAGE));
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	return change;
}