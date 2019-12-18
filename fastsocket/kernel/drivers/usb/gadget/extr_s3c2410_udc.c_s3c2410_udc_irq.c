#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ speed; } ;
struct s3c2410_udc {int /*<<< orphan*/  lock; TYPE_5__* ep; void* ep0state; TYPE_3__ gadget; TYPE_2__* driver; scalar_t__ address; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int maxpacket; } ;
struct TYPE_9__ {TYPE_1__ ep; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* suspend ) (TYPE_3__*) ;int /*<<< orphan*/  (* resume ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_NORMAL ; 
 int /*<<< orphan*/  DEBUG_VERBOSE ; 
 void* EP0_IDLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IRQ_USBD ; 
 int S3C2410_ENDPOINTS ; 
 int /*<<< orphan*/  S3C2410_UDC_EP_INT_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_INDEX_EP0 ; 
 int /*<<< orphan*/  S3C2410_UDC_INDEX_REG ; 
 int S3C2410_UDC_INT_EP0 ; 
 int /*<<< orphan*/  S3C2410_UDC_IN_CSR1_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_MAXP_REG ; 
 int /*<<< orphan*/  S3C2410_UDC_PWR_REG ; 
 int S3C2410_UDC_USBINT_RESET ; 
 int S3C2410_UDC_USBINT_RESUME ; 
 int S3C2410_UDC_USBINT_SUSPEND ; 
 int /*<<< orphan*/  S3C2410_UDC_USB_INT_REG ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  base_addr ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  s3c2410_udc_handle_ep (TYPE_5__*) ; 
 int /*<<< orphan*/  s3c2410_udc_handle_ep0 (struct s3c2410_udc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int udc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t s3c2410_udc_irq(int dummy, void *_dev)
{
	struct s3c2410_udc *dev = _dev;
	int usb_status;
	int usbd_status;
	int pwr_reg;
	int ep0csr;
	int i;
	u32 idx;
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);

	/* Driver connected ? */
	if (!dev->driver) {
		/* Clear interrupts */
		udc_write(udc_read(S3C2410_UDC_USB_INT_REG),
				S3C2410_UDC_USB_INT_REG);
		udc_write(udc_read(S3C2410_UDC_EP_INT_REG),
				S3C2410_UDC_EP_INT_REG);
	}

	/* Save index */
	idx = udc_read(S3C2410_UDC_INDEX_REG);

	/* Read status registers */
	usb_status = udc_read(S3C2410_UDC_USB_INT_REG);
	usbd_status = udc_read(S3C2410_UDC_EP_INT_REG);
	pwr_reg = udc_read(S3C2410_UDC_PWR_REG);

	udc_writeb(base_addr, S3C2410_UDC_INDEX_EP0, S3C2410_UDC_INDEX_REG);
	ep0csr = udc_read(S3C2410_UDC_IN_CSR1_REG);

	dprintk(DEBUG_NORMAL, "usbs=%02x, usbds=%02x, pwr=%02x ep0csr=%02x\n",
		usb_status, usbd_status, pwr_reg, ep0csr);

	/*
	 * Now, handle interrupts. There's two types :
	 * - Reset, Resume, Suspend coming -> usb_int_reg
	 * - EP -> ep_int_reg
	 */

	/* RESET */
	if (usb_status & S3C2410_UDC_USBINT_RESET) {
		/* two kind of reset :
		 * - reset start -> pwr reg = 8
		 * - reset end   -> pwr reg = 0
		 **/
		dprintk(DEBUG_NORMAL, "USB reset csr %x pwr %x\n",
			ep0csr, pwr_reg);

		dev->gadget.speed = USB_SPEED_UNKNOWN;
		udc_write(0x00, S3C2410_UDC_INDEX_REG);
		udc_write((dev->ep[0].ep.maxpacket & 0x7ff) >> 3,
				S3C2410_UDC_MAXP_REG);
		dev->address = 0;

		dev->ep0state = EP0_IDLE;
		dev->gadget.speed = USB_SPEED_FULL;

		/* clear interrupt */
		udc_write(S3C2410_UDC_USBINT_RESET,
				S3C2410_UDC_USB_INT_REG);

		udc_write(idx, S3C2410_UDC_INDEX_REG);
		spin_unlock_irqrestore(&dev->lock, flags);
		return IRQ_HANDLED;
	}

	/* RESUME */
	if (usb_status & S3C2410_UDC_USBINT_RESUME) {
		dprintk(DEBUG_NORMAL, "USB resume\n");

		/* clear interrupt */
		udc_write(S3C2410_UDC_USBINT_RESUME,
				S3C2410_UDC_USB_INT_REG);

		if (dev->gadget.speed != USB_SPEED_UNKNOWN
				&& dev->driver
				&& dev->driver->resume)
			dev->driver->resume(&dev->gadget);
	}

	/* SUSPEND */
	if (usb_status & S3C2410_UDC_USBINT_SUSPEND) {
		dprintk(DEBUG_NORMAL, "USB suspend\n");

		/* clear interrupt */
		udc_write(S3C2410_UDC_USBINT_SUSPEND,
				S3C2410_UDC_USB_INT_REG);

		if (dev->gadget.speed != USB_SPEED_UNKNOWN
				&& dev->driver
				&& dev->driver->suspend)
			dev->driver->suspend(&dev->gadget);

		dev->ep0state = EP0_IDLE;
	}

	/* EP */
	/* control traffic */
	/* check on ep0csr != 0 is not a good idea as clearing in_pkt_ready
	 * generate an interrupt
	 */
	if (usbd_status & S3C2410_UDC_INT_EP0) {
		dprintk(DEBUG_VERBOSE, "USB ep0 irq\n");
		/* Clear the interrupt bit by setting it to 1 */
		udc_write(S3C2410_UDC_INT_EP0, S3C2410_UDC_EP_INT_REG);
		s3c2410_udc_handle_ep0(dev);
	}

	/* endpoint data transfers */
	for (i = 1; i < S3C2410_ENDPOINTS; i++) {
		u32 tmp = 1 << i;
		if (usbd_status & tmp) {
			dprintk(DEBUG_VERBOSE, "USB ep%d irq\n", i);

			/* Clear the interrupt bit by setting it to 1 */
			udc_write(tmp, S3C2410_UDC_EP_INT_REG);
			s3c2410_udc_handle_ep(&dev->ep[i]);
		}
	}

	dprintk(DEBUG_VERBOSE, "irq: %d s3c2410_udc_done.\n", IRQ_USBD);

	/* Restore old index */
	udc_write(idx, S3C2410_UDC_INDEX_REG);

	spin_unlock_irqrestore(&dev->lock, flags);

	return IRQ_HANDLED;
}