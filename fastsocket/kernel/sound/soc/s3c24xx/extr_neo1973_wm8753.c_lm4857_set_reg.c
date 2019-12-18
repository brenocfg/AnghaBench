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
struct soc_mixer_control {int reg; int shift; int max; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int* lm4857_regs ; 
 int /*<<< orphan*/  lm4857_write_regs () ; 

__attribute__((used)) static int lm4857_set_reg(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	int reg = mc->reg;
	int shift = mc->shift;
	int mask = mc->max;

	if (((lm4857_regs[reg] >> shift) & mask) ==
		ucontrol->value.integer.value[0])
		return 0;

	lm4857_regs[reg] &= ~(mask << shift);
	lm4857_regs[reg] |= ucontrol->value.integer.value[0] << shift;
	lm4857_write_regs();
	return 1;
}