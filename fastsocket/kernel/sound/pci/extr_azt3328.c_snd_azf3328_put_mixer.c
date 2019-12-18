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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_azf3328 {int dummy; } ;
struct azf3328_mixer_reg {int mask; int lchan_shift; int rchan_shift; int /*<<< orphan*/  reg; scalar_t__ invert; scalar_t__ stereo; } ;

/* Variables and functions */
 int SET_CHAN_LEFT ; 
 int SET_CHAN_RIGHT ; 
 int /*<<< orphan*/  snd_azf3328_dbgcallenter () ; 
 int /*<<< orphan*/  snd_azf3328_dbgcallleave () ; 
 int /*<<< orphan*/  snd_azf3328_dbgmixer (char*,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int snd_azf3328_mixer_inw (struct snd_azf3328*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_outw (struct snd_azf3328*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_reg_decode (struct azf3328_mixer_reg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_write_volume_gradually (struct snd_azf3328*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 struct snd_azf3328* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int
snd_azf3328_put_mixer(struct snd_kcontrol *kcontrol,
		      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_azf3328 *chip = snd_kcontrol_chip(kcontrol);
	struct azf3328_mixer_reg reg;
	u16 oreg, nreg, val;

	snd_azf3328_dbgcallenter();
	snd_azf3328_mixer_reg_decode(&reg, kcontrol->private_value);
	oreg = snd_azf3328_mixer_inw(chip, reg.reg);
	val = ucontrol->value.integer.value[0] & reg.mask;
	if (reg.invert)
		val = reg.mask - val;
	nreg = oreg & ~(reg.mask << reg.lchan_shift);
	nreg |= (val << reg.lchan_shift);
	if (reg.stereo) {
		val = ucontrol->value.integer.value[1] & reg.mask;
		if (reg.invert)
			val = reg.mask - val;
		nreg &= ~(reg.mask << reg.rchan_shift);
		nreg |= (val << reg.rchan_shift);
	}
	if (reg.mask >= 0x07) /* it's a volume control, so better take care */
		snd_azf3328_mixer_write_volume_gradually(
			chip, reg.reg, nreg >> 8, nreg & 0xff,
			/* just set both channels, doesn't matter */
			SET_CHAN_LEFT|SET_CHAN_RIGHT,
			0);
	else
        	snd_azf3328_mixer_outw(chip, reg.reg, nreg);

	snd_azf3328_dbgmixer("put: %02x to %02lx|%02lx, "
			     "oreg %04x; shift %02d|%02d -> nreg %04x; after: %04x\n",
		reg.reg, ucontrol->value.integer.value[0], ucontrol->value.integer.value[1],
		oreg, reg.lchan_shift, reg.rchan_shift,
		nreg, snd_azf3328_mixer_inw(chip, reg.reg));
	snd_azf3328_dbgcallleave();
	return (nreg != oreg);
}