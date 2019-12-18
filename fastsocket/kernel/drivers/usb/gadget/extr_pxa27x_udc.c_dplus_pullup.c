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
struct pxa_udc {int pullup_on; TYPE_1__* mach; } ;
struct TYPE_2__ {int gpio_pullup_inverted; int /*<<< orphan*/  (* udc_command ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  gpio_pullup; } ;

/* Variables and functions */
 int /*<<< orphan*/  PXA2XX_UDC_CMD_CONNECT ; 
 int /*<<< orphan*/  PXA2XX_UDC_CMD_DISCONNECT ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dplus_pullup(struct pxa_udc *udc, int on)
{
	if (on) {
		if (gpio_is_valid(udc->mach->gpio_pullup))
			gpio_set_value(udc->mach->gpio_pullup,
				       !udc->mach->gpio_pullup_inverted);
		if (udc->mach->udc_command)
			udc->mach->udc_command(PXA2XX_UDC_CMD_CONNECT);
	} else {
		if (gpio_is_valid(udc->mach->gpio_pullup))
			gpio_set_value(udc->mach->gpio_pullup,
				       udc->mach->gpio_pullup_inverted);
		if (udc->mach->udc_command)
			udc->mach->udc_command(PXA2XX_UDC_CMD_DISCONNECT);
	}
	udc->pullup_on = on;
}