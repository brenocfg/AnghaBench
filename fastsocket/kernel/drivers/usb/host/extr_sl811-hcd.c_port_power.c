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
struct TYPE_4__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_2__ self; int /*<<< orphan*/  state; } ;
struct sl811 {int port1; int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  ctrl1; TYPE_1__* board; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* port_power ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,char*) ; 
 int /*<<< orphan*/  HC_STATE_HALT ; 
 int /*<<< orphan*/  SL11H_CTL1MASK_SE0 ; 
 int /*<<< orphan*/  SL11H_CTLREG1 ; 
 int /*<<< orphan*/  SL11H_INTMASK_INSRMV ; 
 int /*<<< orphan*/  SL11H_IRQ_ENABLE ; 
 int /*<<< orphan*/  SL11H_IRQ_STATUS ; 
 int /*<<< orphan*/  SL811HS_CTL2_INIT ; 
 int /*<<< orphan*/  SL811HS_CTLREG2 ; 
 int USB_PORT_FEAT_POWER ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct usb_hcd* sl811_to_hcd (struct sl811*) ; 
 int /*<<< orphan*/  sl811_write (struct sl811*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_power(struct sl811 *sl811, int is_on)
{
	struct usb_hcd	*hcd = sl811_to_hcd(sl811);

	/* hub is inactive unless the port is powered */
	if (is_on) {
		if (sl811->port1 & (1 << USB_PORT_FEAT_POWER))
			return;

		sl811->port1 = (1 << USB_PORT_FEAT_POWER);
		sl811->irq_enable = SL11H_INTMASK_INSRMV;
	} else {
		sl811->port1 = 0;
		sl811->irq_enable = 0;
		hcd->state = HC_STATE_HALT;
	}
	sl811->ctrl1 = 0;
	sl811_write(sl811, SL11H_IRQ_ENABLE, 0);
	sl811_write(sl811, SL11H_IRQ_STATUS, ~0);

	if (sl811->board && sl811->board->port_power) {
		/* switch VBUS, at 500mA unless hub power budget gets set */
		DBG("power %s\n", is_on ? "on" : "off");
		sl811->board->port_power(hcd->self.controller, is_on);
	}

	/* reset as thoroughly as we can */
	if (sl811->board && sl811->board->reset)
		sl811->board->reset(hcd->self.controller);
	else {
		sl811_write(sl811, SL11H_CTLREG1, SL11H_CTL1MASK_SE0);
		mdelay(20);
	}

	sl811_write(sl811, SL11H_IRQ_ENABLE, 0);
	sl811_write(sl811, SL11H_CTLREG1, sl811->ctrl1);
	sl811_write(sl811, SL811HS_CTLREG2, SL811HS_CTL2_INIT);
	sl811_write(sl811, SL11H_IRQ_ENABLE, sl811->irq_enable);

	// if !is_on, put into lowpower mode now
}