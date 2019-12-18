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
struct snd_es18xx {int version; } ;
struct TYPE_4__ {unsigned char* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char snd_es18xx_mixer_bits (struct snd_es18xx*,int,int,unsigned char) ; 
 struct snd_es18xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_es18xx_put_mux(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	static unsigned char map4Source[4] = {0, 2, 6, 7};
	struct snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	unsigned char val = ucontrol->value.enumerated.item[0];
	unsigned char retVal = 0;

	switch (chip->version) {
 /* 5 source chips */
	case 0x1887:
	case 0x1888:
		if (val > 4)
			return -EINVAL;
		if (val == 4) {
			retVal = snd_es18xx_mixer_bits(chip, 0x7a, 0x08, 0x08) != 0x08;
			val = 3;
		} else
			retVal = snd_es18xx_mixer_bits(chip, 0x7a, 0x08, 0x00) != 0x00;
 /* 4 source chips */
	case 0x1868:
	case 0x1878:
		if (val > 3)
			return -EINVAL;
		val = map4Source[val];
		break;
 /* 8 source chips */
	case 0x1869:
	case 0x1879:
		if (val > 7)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}
	return (snd_es18xx_mixer_bits(chip, 0x1c, 0x07, val) != val) || retVal;
}