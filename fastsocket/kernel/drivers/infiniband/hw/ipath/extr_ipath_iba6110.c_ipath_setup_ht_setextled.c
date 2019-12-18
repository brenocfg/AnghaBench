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
typedef  scalar_t__ u64 ;
struct ipath_devdata {int ipath_led_override; int ipath_boardrev; scalar_t__ ipath_extctrl; int /*<<< orphan*/  ipath_gpio_lock; TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_extctrl; } ;

/* Variables and functions */
 scalar_t__ INFINIPATH_EXTC_LED1PRIPORT_ON ; 
 scalar_t__ INFINIPATH_EXTC_LED2PRIPORT_ON ; 
 scalar_t__ INFINIPATH_EXTC_LEDGBLERR_OFF ; 
 scalar_t__ INFINIPATH_EXTC_LEDGBLOK_ON ; 
 scalar_t__ INFINIPATH_IBCS_LT_STATE_DISABLED ; 
 scalar_t__ INFINIPATH_IBCS_LT_STATE_LINKUP ; 
 scalar_t__ INFINIPATH_IBCS_L_STATE_ACTIVE ; 
 scalar_t__ INFINIPATH_IBCS_L_STATE_DOWN ; 
 int IPATH_LED_LOG ; 
 int IPATH_LED_PHYS ; 
 scalar_t__ ipath_diag_inuse ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipath_setup_ht_setextled(struct ipath_devdata *dd,
				     u64 lst, u64 ltst)
{
	u64 extctl;
	unsigned long flags = 0;

	/* the diags use the LED to indicate diag info, so we leave
	 * the external LED alone when the diags are running */
	if (ipath_diag_inuse)
		return;

	/* Allow override of LED display for, e.g. Locating system in rack */
	if (dd->ipath_led_override) {
		ltst = (dd->ipath_led_override & IPATH_LED_PHYS)
			? INFINIPATH_IBCS_LT_STATE_LINKUP
			: INFINIPATH_IBCS_LT_STATE_DISABLED;
		lst = (dd->ipath_led_override & IPATH_LED_LOG)
			? INFINIPATH_IBCS_L_STATE_ACTIVE
			: INFINIPATH_IBCS_L_STATE_DOWN;
	}

	spin_lock_irqsave(&dd->ipath_gpio_lock, flags);
	/*
	 * start by setting both LED control bits to off, then turn
	 * on the appropriate bit(s).
	 */
	if (dd->ipath_boardrev == 8) { /* LS/X-1 uses different pins */
		/*
		 * major difference is that INFINIPATH_EXTC_LEDGBLERR_OFF
		 * is inverted,  because it is normally used to indicate
		 * a hardware fault at reset, if there were errors
		 */
		extctl = (dd->ipath_extctrl & ~INFINIPATH_EXTC_LEDGBLOK_ON)
			| INFINIPATH_EXTC_LEDGBLERR_OFF;
		if (ltst == INFINIPATH_IBCS_LT_STATE_LINKUP)
			extctl &= ~INFINIPATH_EXTC_LEDGBLERR_OFF;
		if (lst == INFINIPATH_IBCS_L_STATE_ACTIVE)
			extctl |= INFINIPATH_EXTC_LEDGBLOK_ON;
	}
	else {
		extctl = dd->ipath_extctrl &
			~(INFINIPATH_EXTC_LED1PRIPORT_ON |
			  INFINIPATH_EXTC_LED2PRIPORT_ON);
		if (ltst == INFINIPATH_IBCS_LT_STATE_LINKUP)
			extctl |= INFINIPATH_EXTC_LED1PRIPORT_ON;
		if (lst == INFINIPATH_IBCS_L_STATE_ACTIVE)
			extctl |= INFINIPATH_EXTC_LED2PRIPORT_ON;
	}
	dd->ipath_extctrl = extctl;
	ipath_write_kreg(dd, dd->ipath_kregs->kr_extctrl, extctl);
	spin_unlock_irqrestore(&dd->ipath_gpio_lock, flags);
}