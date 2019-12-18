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
struct TYPE_2__ {int /*<<< orphan*/  vbus_pin; } ;
struct at91_udc {unsigned int vbus; int /*<<< orphan*/  gadget; TYPE_1__ board; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  at91_vbus_session (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static irqreturn_t at91_vbus_irq(int irq, void *_udc)
{
	struct at91_udc	*udc = _udc;
	unsigned	value;

	/* vbus needs at least brief debouncing */
	udelay(10);
	value = gpio_get_value(udc->board.vbus_pin);
	if (value != udc->vbus)
		at91_vbus_session(&udc->gadget, value);

	return IRQ_HANDLED;
}