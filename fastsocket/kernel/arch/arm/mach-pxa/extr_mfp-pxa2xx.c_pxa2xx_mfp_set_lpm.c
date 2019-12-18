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
 unsigned long MFP_LPM_STATE_MASK ; 
 int /*<<< orphan*/  __mfp_config_gpio (int,unsigned long) ; 
 int __mfp_validate (int) ; 
 TYPE_1__* gpio_desc ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void pxa2xx_mfp_set_lpm(int mfp, unsigned long lpm)
{
	unsigned long flags, c;
	int gpio;

	gpio = __mfp_validate(mfp);
	if (gpio < 0)
		return;

	local_irq_save(flags);

	c = gpio_desc[gpio].config;
	c = (c & ~MFP_LPM_STATE_MASK) | lpm;
	__mfp_config_gpio(gpio, c);

	local_irq_restore(flags);
}