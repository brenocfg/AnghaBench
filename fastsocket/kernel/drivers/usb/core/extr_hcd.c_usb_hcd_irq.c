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
struct usb_hcd {TYPE_1__* shared_hcd; int /*<<< orphan*/  flags; TYPE_2__* driver; } ;
typedef  scalar_t__ irqreturn_t ;
struct TYPE_4__ {scalar_t__ (* irq ) (struct usb_hcd*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ HCD_DEAD (struct usb_hcd*) ; 
 int /*<<< orphan*/  HCD_FLAG_SAW_IRQ ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct usb_hcd*) ; 
 scalar_t__ unlikely (int) ; 

irqreturn_t usb_hcd_irq (int irq, void *__hcd)
{
	struct usb_hcd		*hcd = __hcd;
	unsigned long		flags;
	irqreturn_t		rc;

	/* IRQF_DISABLED doesn't work correctly with shared IRQs
	 * when the first handler doesn't use it.  So let's just
	 * assume it's never used.
	 */
	local_irq_save(flags);

	if (unlikely(HCD_DEAD(hcd) || !HCD_HW_ACCESSIBLE(hcd))) {
		rc = IRQ_NONE;
	} else if (hcd->driver->irq(hcd) == IRQ_NONE) {
		rc = IRQ_NONE;
	} else {
		set_bit(HCD_FLAG_SAW_IRQ, &hcd->flags);
		if (hcd->shared_hcd)
			set_bit(HCD_FLAG_SAW_IRQ, &hcd->shared_hcd->flags);
		rc = IRQ_HANDLED;
	}

	local_irq_restore(flags);
	return rc;
}