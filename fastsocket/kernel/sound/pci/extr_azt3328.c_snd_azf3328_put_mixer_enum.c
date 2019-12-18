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
typedef  int u16 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_azf3328 {int dummy; } ;
struct azf3328_mixer_reg {scalar_t__ reg; unsigned int enum_c; int lchan_shift; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IDX_MIXER_REC_SELECT ; 
 int /*<<< orphan*/  snd_azf3328_dbgmixer (char*,scalar_t__,int,int) ; 
 int snd_azf3328_mixer_inw (struct snd_azf3328*,scalar_t__) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_outw (struct snd_azf3328*,scalar_t__,int) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_reg_decode (struct azf3328_mixer_reg*,int /*<<< orphan*/ ) ; 
 struct snd_azf3328* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int
snd_azf3328_put_mixer_enum(struct snd_kcontrol *kcontrol,
			   struct snd_ctl_elem_value *ucontrol)
{
        struct snd_azf3328 *chip = snd_kcontrol_chip(kcontrol);
	struct azf3328_mixer_reg reg;
	u16 oreg, nreg, val;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->private_value);
	oreg = snd_azf3328_mixer_inw(chip, reg.reg);
	val = oreg;
	if (reg.reg == IDX_MIXER_REC_SELECT) {
        	if (ucontrol->value.enumerated.item[0] > reg.enum_c - 1U ||
            	ucontrol->value.enumerated.item[1] > reg.enum_c - 1U)
                	return -EINVAL;
        	val = (ucontrol->value.enumerated.item[0] << 8) |
        	      (ucontrol->value.enumerated.item[1] << 0);
	} else {
        	if (ucontrol->value.enumerated.item[0] > reg.enum_c - 1U)
                	return -EINVAL;
		val &= ~((reg.enum_c - 1) << reg.lchan_shift);
        	val |= (ucontrol->value.enumerated.item[0] << reg.lchan_shift);
	}
	snd_azf3328_mixer_outw(chip, reg.reg, val);
	nreg = val;

	snd_azf3328_dbgmixer("put_enum: %02x to %04x, oreg %04x\n", reg.reg, val, oreg);
	return (nreg != oreg);
}