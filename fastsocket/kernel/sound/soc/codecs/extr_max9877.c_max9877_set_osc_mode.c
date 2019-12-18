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
typedef  int u8 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int MAX9877_OSC_MASK ; 
 int MAX9877_OSC_OFFSET ; 
 size_t MAX9877_OUTPUT_MODE ; 
 int* max9877_regs ; 
 int /*<<< orphan*/  max9877_write_regs () ; 

__attribute__((used)) static int max9877_set_osc_mode(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	u8 value = ucontrol->value.integer.value[0];

	value = value << MAX9877_OSC_OFFSET;
	if ((max9877_regs[MAX9877_OUTPUT_MODE] & MAX9877_OSC_MASK) == value)
		return 0;

	max9877_regs[MAX9877_OUTPUT_MODE] &= ~MAX9877_OSC_MASK;
	max9877_regs[MAX9877_OUTPUT_MODE] |= value;
	max9877_write_regs();
	return 1;
}