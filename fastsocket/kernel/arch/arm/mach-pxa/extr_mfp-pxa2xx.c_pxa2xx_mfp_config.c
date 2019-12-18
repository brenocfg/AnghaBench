#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long config; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFP_PIN (unsigned long) ; 
 int /*<<< orphan*/  __mfp_config_gpio (int,unsigned long) ; 
 int __mfp_validate (int /*<<< orphan*/ ) ; 
 TYPE_1__* gpio_desc ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void pxa2xx_mfp_config(unsigned long *mfp_cfgs, int num)
{
	unsigned long flags;
	unsigned long *c;
	int i, gpio;

	for (i = 0, c = mfp_cfgs; i < num; i++, c++) {

		gpio = __mfp_validate(MFP_PIN(*c));
		if (gpio < 0)
			continue;

		local_irq_save(flags);

		gpio_desc[gpio].config = *c;
		__mfp_config_gpio(gpio, *c);

		local_irq_restore(flags);
	}
}