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
struct pxa2xx_udc_mach_info {int (* udc_is_connected ) () ;scalar_t__ gpio_vbus_inverted; int /*<<< orphan*/  gpio_vbus; } ;
struct TYPE_2__ {struct pxa2xx_udc_mach_info* mach; } ;

/* Variables and functions */
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int stub1 () ; 
 TYPE_1__* the_controller ; 

__attribute__((used)) static int is_vbus_present(void)
{
	struct pxa2xx_udc_mach_info		*mach = the_controller->mach;

	if (gpio_is_valid(mach->gpio_vbus)) {
		int value = gpio_get_value(mach->gpio_vbus);

		if (mach->gpio_vbus_inverted)
			return !value;
		else
			return !!value;
	}
	if (mach->udc_is_connected)
		return mach->udc_is_connected();
	return 1;
}