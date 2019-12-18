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
struct usba_udc {int /*<<< orphan*/  vbus_pin; } ;

/* Variables and functions */
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vbus_is_present(struct usba_udc *udc)
{
	if (gpio_is_valid(udc->vbus_pin))
		return gpio_get_value(udc->vbus_pin);

	/* No Vbus detection: Assume always present */
	return 1;
}