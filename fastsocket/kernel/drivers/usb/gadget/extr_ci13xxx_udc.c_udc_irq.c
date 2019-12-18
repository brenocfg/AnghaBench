#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  speed; } ;
struct ci13xxx {int /*<<< orphan*/  lock; TYPE_2__ gadget; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int* buf; int /*<<< orphan*/  cnt; int /*<<< orphan*/  idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  none; int /*<<< orphan*/  sli; int /*<<< orphan*/  ui; int /*<<< orphan*/  uei; int /*<<< orphan*/  pci; int /*<<< orphan*/  uri; TYPE_1__ hndl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISR_MASK ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int USBi_PCI ; 
 int USBi_SLI ; 
 int USBi_UEI ; 
 int USBi_UI ; 
 int USBi_URI ; 
 struct ci13xxx* _udc ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ hw_port_is_high_speed () ; 
 int hw_test_and_clear_intr_active () ; 
 int /*<<< orphan*/  isr_reset_handler (struct ci13xxx*) ; 
 TYPE_3__ isr_statistics ; 
 int /*<<< orphan*/  isr_tr_complete_handler (struct ci13xxx*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace () ; 

__attribute__((used)) static irqreturn_t udc_irq(void)
{
	struct ci13xxx *udc = _udc;
	irqreturn_t retval;
	u32 intr;

	trace();

	if (udc == NULL) {
		err("ENODEV");
		return IRQ_HANDLED;
	}

	spin_lock(udc->lock);
	intr = hw_test_and_clear_intr_active();
	if (intr) {
		isr_statistics.hndl.buf[isr_statistics.hndl.idx++] = intr;
		isr_statistics.hndl.idx &= ISR_MASK;
		isr_statistics.hndl.cnt++;

		/* order defines priority - do NOT change it */
		if (USBi_URI & intr) {
			isr_statistics.uri++;
			isr_reset_handler(udc);
		}
		if (USBi_PCI & intr) {
			isr_statistics.pci++;
			udc->gadget.speed = hw_port_is_high_speed() ?
				USB_SPEED_HIGH : USB_SPEED_FULL;
		}
		if (USBi_UEI & intr)
			isr_statistics.uei++;
		if (USBi_UI  & intr) {
			isr_statistics.ui++;
			isr_tr_complete_handler(udc);
		}
		if (USBi_SLI & intr)
			isr_statistics.sli++;
		retval = IRQ_HANDLED;
	} else {
		isr_statistics.none++;
		retval = IRQ_NONE;
	}
	spin_unlock(udc->lock);

	return retval;
}