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
struct soc_mixer_control {unsigned int reg; unsigned int rreg; unsigned int shift; unsigned int max; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned int* max9877_regs ; 
 int /*<<< orphan*/  max9877_write_regs () ; 

__attribute__((used)) static int max9877_set_2reg(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	unsigned int reg = mc->reg;
	unsigned int reg2 = mc->rreg;
	unsigned int shift = mc->shift;
	unsigned int mask = mc->max;
	unsigned int val = (ucontrol->value.integer.value[0] & mask);
	unsigned int val2 = (ucontrol->value.integer.value[1] & mask);
	unsigned int change = 1;

	if (((max9877_regs[reg] >> shift) & mask) == val)
		change = 0;

	if (((max9877_regs[reg2] >> shift) & mask) == val2)
		change = 0;

	if (change) {
		max9877_regs[reg] &= ~(mask << shift);
		max9877_regs[reg] |= val << shift;
		max9877_regs[reg2] &= ~(mask << shift);
		max9877_regs[reg2] |= val2 << shift;
		max9877_write_regs();
	}

	return change;
}