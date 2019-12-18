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
struct pxa_udc {int /*<<< orphan*/  transceiver; scalar_t__ vbus_sensed; scalar_t__ driver; scalar_t__ pullup_on; } ;

/* Variables and functions */

__attribute__((used)) static int should_enable_udc(struct pxa_udc *udc)
{
	int put_on;

	put_on = ((udc->pullup_on) && (udc->driver));
	put_on &= ((udc->vbus_sensed) || (!udc->transceiver));
	return put_on;
}