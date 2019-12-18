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
struct TYPE_3__ {unsigned short* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_azf3328 {int dummy; } ;
struct azf3328_mixer_reg {scalar_t__ reg; int enum_c; unsigned short lchan_shift; } ;

/* Variables and functions */
 scalar_t__ IDX_MIXER_REC_SELECT ; 
 int /*<<< orphan*/  snd_azf3328_dbgmixer (char*,scalar_t__,unsigned short,unsigned short,unsigned short,unsigned short,int) ; 
 unsigned short snd_azf3328_mixer_inw (struct snd_azf3328*,scalar_t__) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_reg_decode (struct azf3328_mixer_reg*,int /*<<< orphan*/ ) ; 
 struct snd_azf3328* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int
snd_azf3328_get_mixer_enum(struct snd_kcontrol *kcontrol,
			   struct snd_ctl_elem_value *ucontrol)
{
        struct snd_azf3328 *chip = snd_kcontrol_chip(kcontrol);
	struct azf3328_mixer_reg reg;
        unsigned short val;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->private_value);
	val = snd_azf3328_mixer_inw(chip, reg.reg);
	if (reg.reg == IDX_MIXER_REC_SELECT) {
        	ucontrol->value.enumerated.item[0] = (val >> 8) & (reg.enum_c - 1);
        	ucontrol->value.enumerated.item[1] = (val >> 0) & (reg.enum_c - 1);
	} else
        	ucontrol->value.enumerated.item[0] = (val >> reg.lchan_shift) & (reg.enum_c - 1);

	snd_azf3328_dbgmixer("get_enum: %02x is %04x -> %d|%d (shift %02d, enum_c %d)\n",
		reg.reg, val, ucontrol->value.enumerated.item[0], ucontrol->value.enumerated.item[1],
		reg.lchan_shift, reg.enum_c);
        return 0;
}