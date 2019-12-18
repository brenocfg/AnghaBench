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
struct pxa_udc {scalar_t__ transceiver; int /*<<< orphan*/  vbus_sensed; int /*<<< orphan*/  driver; int /*<<< orphan*/  pullup_on; } ;

/* Variables and functions */

__attribute__((used)) static int should_disable_udc(struct pxa_udc *udc)
{
	int put_off;

	put_off = ((!udc->pullup_on) || (!udc->driver));
	put_off |= ((!udc->vbus_sensed) && (udc->transceiver));
	return put_off;
}