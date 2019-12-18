#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_8__ {scalar_t__ speed; } ;
struct omap_udc {int devstat; int /*<<< orphan*/  lock; TYPE_3__ gadget; TYPE_2__* driver; scalar_t__ transceiver; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* resume ) (TYPE_3__*) ;int /*<<< orphan*/  (* suspend ) (TYPE_3__*) ;TYPE_1__ driver; int /*<<< orphan*/  (* disconnect ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFO (char*,int /*<<< orphan*/ ) ; 
 int OTG_FLAGS ; 
 int UDC_ADD ; 
 int UDC_ATT ; 
 int UDC_CFG ; 
 int UDC_DEF ; 
 int /*<<< orphan*/  UDC_DEVSTAT ; 
 int UDC_DS_CHG ; 
 int UDC_DS_CHG_IE ; 
 int UDC_EP0_IE ; 
 int /*<<< orphan*/  UDC_IRQ_EN ; 
 int /*<<< orphan*/  UDC_IRQ_SRC ; 
 int UDC_SUS ; 
 int UDC_USB_RESET ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  VDBG (char*,...) ; 
 int /*<<< orphan*/  cpu_is_omap15xx () ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_set_suspend (scalar_t__,int) ; 
 int /*<<< orphan*/  pullup_disable (struct omap_udc*) ; 
 int /*<<< orphan*/  pullup_enable (struct omap_udc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  udc_quiesce (struct omap_udc*) ; 
 int /*<<< orphan*/  update_otg (struct omap_udc*) ; 

__attribute__((used)) static void devstate_irq(struct omap_udc *udc, u16 irq_src)
{
	u16	devstat, change;

	devstat = omap_readw(UDC_DEVSTAT);
	change = devstat ^ udc->devstat;
	udc->devstat = devstat;

	if (change & (UDC_USB_RESET|UDC_ATT)) {
		udc_quiesce(udc);

		if (change & UDC_ATT) {
			/* driver for any external transceiver will
			 * have called omap_vbus_session() already
			 */
			if (devstat & UDC_ATT) {
				udc->gadget.speed = USB_SPEED_FULL;
				VDBG("connect\n");
				if (!udc->transceiver)
					pullup_enable(udc);
				// if (driver->connect) call it
			} else if (udc->gadget.speed != USB_SPEED_UNKNOWN) {
				udc->gadget.speed = USB_SPEED_UNKNOWN;
				if (!udc->transceiver)
					pullup_disable(udc);
				DBG("disconnect, gadget %s\n",
					udc->driver->driver.name);
				if (udc->driver->disconnect) {
					spin_unlock(&udc->lock);
					udc->driver->disconnect(&udc->gadget);
					spin_lock(&udc->lock);
				}
			}
			change &= ~UDC_ATT;
		}

		if (change & UDC_USB_RESET) {
			if (devstat & UDC_USB_RESET) {
				VDBG("RESET=1\n");
			} else {
				udc->gadget.speed = USB_SPEED_FULL;
				INFO("USB reset done, gadget %s\n",
					udc->driver->driver.name);
				/* ep0 traffic is legal from now on */
				omap_writew(UDC_DS_CHG_IE | UDC_EP0_IE,
						UDC_IRQ_EN);
			}
			change &= ~UDC_USB_RESET;
		}
	}
	if (change & UDC_SUS) {
		if (udc->gadget.speed != USB_SPEED_UNKNOWN) {
			// FIXME tell isp1301 to suspend/resume (?)
			if (devstat & UDC_SUS) {
				VDBG("suspend\n");
				update_otg(udc);
				/* HNP could be under way already */
				if (udc->gadget.speed == USB_SPEED_FULL
						&& udc->driver->suspend) {
					spin_unlock(&udc->lock);
					udc->driver->suspend(&udc->gadget);
					spin_lock(&udc->lock);
				}
				if (udc->transceiver)
					otg_set_suspend(udc->transceiver, 1);
			} else {
				VDBG("resume\n");
				if (udc->transceiver)
					otg_set_suspend(udc->transceiver, 0);
				if (udc->gadget.speed == USB_SPEED_FULL
						&& udc->driver->resume) {
					spin_unlock(&udc->lock);
					udc->driver->resume(&udc->gadget);
					spin_lock(&udc->lock);
				}
			}
		}
		change &= ~UDC_SUS;
	}
	if (!cpu_is_omap15xx() && (change & OTG_FLAGS)) {
		update_otg(udc);
		change &= ~OTG_FLAGS;
	}

	change &= ~(UDC_CFG|UDC_DEF|UDC_ADD);
	if (change)
		VDBG("devstat %03x, ignore change %03x\n",
			devstat,  change);

	omap_writew(UDC_DS_CHG, UDC_IRQ_SRC);
}