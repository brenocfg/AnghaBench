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
struct snd_pmac {int dummy; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned int BASE2ADDR (int) ; 
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_pmac_burgundy_rcb (struct snd_pmac*,unsigned int) ; 
 int /*<<< orphan*/  snd_pmac_burgundy_wcb (struct snd_pmac*,unsigned int,int) ; 

__attribute__((used)) static int snd_pmac_burgundy_put_gain(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	unsigned int addr = BASE2ADDR(kcontrol->private_value & 0xff);
	int stereo = (kcontrol->private_value >> 24) & 1;
	int atten = (kcontrol->private_value >> 25) & 1;
	int oval, val;

	oval = snd_pmac_burgundy_rcb(chip, addr);
	if (atten)
		oval = ~oval & 0xff;
	val = ucontrol->value.integer.value[0];
	if (stereo)
		val |= ucontrol->value.integer.value[1] << 4;
	else
		val |= ucontrol->value.integer.value[0] << 4;
	if (atten)
		val = ~val & 0xff;
	snd_pmac_burgundy_wcb(chip, addr, val);
	return val != oval;
}