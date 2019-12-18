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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {unsigned short* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {unsigned short* regs; } ;

/* Variables and functions */
 unsigned short AC97_AD1986_MVREF0 ; 
 unsigned short AC97_AD1986_MVREF1 ; 
 unsigned short AC97_AD1986_MVREF2 ; 
 size_t AC97_AD_MISC2 ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_ad1986_vrefout_get(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	/* Use MIC_1/2 V_REFOUT as the "get" value */
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	unsigned short val;
	unsigned short reg = ac97->regs[AC97_AD_MISC2];
	if ((reg & AC97_AD1986_MVREF0) != 0)
		val = 2;
	else if ((reg & AC97_AD1986_MVREF1) != 0)
		val = 3;
	else if ((reg & AC97_AD1986_MVREF2) != 0)
		val = 1;
	else
		val = 0;
	ucontrol->value.enumerated.item[0] = val;
	return 0;
}