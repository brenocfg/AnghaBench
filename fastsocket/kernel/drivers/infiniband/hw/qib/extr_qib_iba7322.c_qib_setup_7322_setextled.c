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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct qib_pportdata {int led_override; int port; struct qib_devdata* dd; } ;
struct qib_devdata {TYPE_1__* cspec; scalar_t__ diag_client; } ;
struct TYPE_2__ {int extctrl; int /*<<< orphan*/  gpio_lock; } ;

/* Variables and functions */
 int ExtLED_IB1_GRN ; 
 int ExtLED_IB1_MASK ; 
 int ExtLED_IB1_YEL ; 
 int ExtLED_IB2_GRN ; 
 int ExtLED_IB2_MASK ; 
 int ExtLED_IB2_YEL ; 
 int IBA7322_LEDBLINK_OFF_SHIFT ; 
 int IBA7322_LEDBLINK_ON_SHIFT ; 
 scalar_t__ IB_PHYSPORTSTATE_LINKUP ; 
 scalar_t__ IB_PORT_ACTIVE ; 
 int QIB_LED_LOG ; 
 int QIB_LED_PHYS ; 
 int /*<<< orphan*/  kr_extctrl ; 
 int /*<<< orphan*/  krp_ibcstatus_a ; 
 int /*<<< orphan*/  krp_rcvpktledcnt ; 
 scalar_t__ qib_7322_iblink_state (int) ; 
 scalar_t__ qib_7322_phys_portstate (int) ; 
 int qib_read_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qib_setup_7322_setextled(struct qib_pportdata *ppd, u32 on)
{
	struct qib_devdata *dd = ppd->dd;
	u64 extctl, ledblink = 0, val;
	unsigned long flags;
	int yel, grn;

	/*
	 * The diags use the LED to indicate diag info, so we leave
	 * the external LED alone when the diags are running.
	 */
	if (dd->diag_client)
		return;

	/* Allow override of LED display for, e.g. Locating system in rack */
	if (ppd->led_override) {
		grn = (ppd->led_override & QIB_LED_PHYS);
		yel = (ppd->led_override & QIB_LED_LOG);
	} else if (on) {
		val = qib_read_kreg_port(ppd, krp_ibcstatus_a);
		grn = qib_7322_phys_portstate(val) ==
			IB_PHYSPORTSTATE_LINKUP;
		yel = qib_7322_iblink_state(val) == IB_PORT_ACTIVE;
	} else {
		grn = 0;
		yel = 0;
	}

	spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
	extctl = dd->cspec->extctrl & (ppd->port == 1 ?
		~ExtLED_IB1_MASK : ~ExtLED_IB2_MASK);
	if (grn) {
		extctl |= ppd->port == 1 ? ExtLED_IB1_GRN : ExtLED_IB2_GRN;
		/*
		 * Counts are in chip clock (4ns) periods.
		 * This is 1/16 sec (66.6ms) on,
		 * 3/16 sec (187.5 ms) off, with packets rcvd.
		 */
		ledblink = ((66600 * 1000UL / 4) << IBA7322_LEDBLINK_ON_SHIFT) |
			((187500 * 1000UL / 4) << IBA7322_LEDBLINK_OFF_SHIFT);
	}
	if (yel)
		extctl |= ppd->port == 1 ? ExtLED_IB1_YEL : ExtLED_IB2_YEL;
	dd->cspec->extctrl = extctl;
	qib_write_kreg(dd, kr_extctrl, dd->cspec->extctrl);
	spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);

	if (ledblink) /* blink the LED on packet receive */
		qib_write_kreg_port(ppd, krp_rcvpktledcnt, ledblink);
}