#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u16 ;
struct soc_mixer_control {unsigned int reg; unsigned int rreg; } ;
struct snd_soc_codec {scalar_t__* reg_cache; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_ctl_elem_value {int dummy; } ;

/* Variables and functions */
 struct snd_soc_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw_2r (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int /*<<< orphan*/  snd_soc_update_bits (struct snd_soc_codec*,unsigned int,int,int) ; 

__attribute__((used)) static int wm8580_out_vu(struct snd_kcontrol *kcontrol,
			 struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	u16 *reg_cache = codec->reg_cache;
	unsigned int reg = mc->reg;
	unsigned int reg2 = mc->rreg;
	int ret;

	/* Clear the register cache so we write without VU set */
	reg_cache[reg] = 0;
	reg_cache[reg2] = 0;

	ret = snd_soc_put_volsw_2r(kcontrol, ucontrol);
	if (ret < 0)
		return ret;

	/* Now write again with the volume update bit set */
	snd_soc_update_bits(codec, reg, 0x100, 0x100);
	snd_soc_update_bits(codec, reg2, 0x100, 0x100);

	return 0;
}