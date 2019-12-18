#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {int /*<<< orphan*/  ep_list; int /*<<< orphan*/  maxpacket; int /*<<< orphan*/  name; } ;
struct udc_ep {size_t num; int in; int naking; scalar_t__ halted; TYPE_2__ ep; TYPE_1__* regs; int /*<<< orphan*/ * dma; int /*<<< orphan*/  desc; int /*<<< orphan*/  fifo_depth; int /*<<< orphan*/  txfifo; struct udc* dev; } ;
struct TYPE_7__ {scalar_t__ speed; TYPE_2__* ep0; } ;
struct udc {scalar_t__ cur_alt; scalar_t__ cur_intf; scalar_t__ cur_config; TYPE_3__ gadget; struct udc_ep* ep; TYPE_4__* regs; TYPE_1__* ep_regs; int /*<<< orphan*/  txfifo; } ;
struct TYPE_8__ {int /*<<< orphan*/  ctl; int /*<<< orphan*/  sts; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 size_t AMD_BIT (int /*<<< orphan*/ ) ; 
 size_t AMD_GETBITS (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (struct udc*,char*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UDC_DEVSTS_ENUM_SPEED ; 
 size_t UDC_DEVSTS_ENUM_SPEED_FULL ; 
 size_t UDC_DEVSTS_ENUM_SPEED_HIGH ; 
 size_t UDC_EP0IN_IX ; 
 int /*<<< orphan*/  UDC_EP0IN_MAX_PKT_SIZE ; 
 size_t UDC_EP0OUT_IX ; 
 int /*<<< orphan*/  UDC_EP0OUT_MAX_PKT_SIZE ; 
 int /*<<< orphan*/  UDC_EPCTL_SNAK ; 
 size_t UDC_EPIN_NUM ; 
 size_t UDC_EP_NUM ; 
 int /*<<< orphan*/  UDC_FS_EP0IN_MAX_PKT_SIZE ; 
 int /*<<< orphan*/  UDC_FS_EP0OUT_MAX_PKT_SIZE ; 
 int /*<<< orphan*/  UDC_RXFIFO_SIZE ; 
 int /*<<< orphan*/  UDC_TXFIFO_SIZE ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  ep_init (TYPE_4__*,struct udc_ep*) ; 
 int /*<<< orphan*/ * ep_string ; 
 size_t readl (int /*<<< orphan*/ *) ; 
 scalar_t__ use_dma ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udc_setup_endpoints(struct udc *dev)
{
	struct udc_ep	*ep;
	u32	tmp;
	u32	reg;

	DBG(dev, "udc_setup_endpoints()\n");

	/* read enum speed */
	tmp = readl(&dev->regs->sts);
	tmp = AMD_GETBITS(tmp, UDC_DEVSTS_ENUM_SPEED);
	if (tmp == UDC_DEVSTS_ENUM_SPEED_HIGH) {
		dev->gadget.speed = USB_SPEED_HIGH;
	} else if (tmp == UDC_DEVSTS_ENUM_SPEED_FULL) {
		dev->gadget.speed = USB_SPEED_FULL;
	}

	/* set basic ep parameters */
	for (tmp = 0; tmp < UDC_EP_NUM; tmp++) {
		ep = &dev->ep[tmp];
		ep->dev = dev;
		ep->ep.name = ep_string[tmp];
		ep->num = tmp;
		/* txfifo size is calculated at enable time */
		ep->txfifo = dev->txfifo;

		/* fifo size */
		if (tmp < UDC_EPIN_NUM) {
			ep->fifo_depth = UDC_TXFIFO_SIZE;
			ep->in = 1;
		} else {
			ep->fifo_depth = UDC_RXFIFO_SIZE;
			ep->in = 0;

		}
		ep->regs = &dev->ep_regs[tmp];
		/*
		 * ep will be reset only if ep was not enabled before to avoid
		 * disabling ep interrupts when ENUM interrupt occurs but ep is
		 * not enabled by gadget driver
		 */
		if (!ep->desc) {
			ep_init(dev->regs, ep);
		}

		if (use_dma) {
			/*
			 * ep->dma is not really used, just to indicate that
			 * DMA is active: remove this
			 * dma regs = dev control regs
			 */
			ep->dma = &dev->regs->ctl;

			/* nak OUT endpoints until enable - not for ep0 */
			if (tmp != UDC_EP0IN_IX && tmp != UDC_EP0OUT_IX
						&& tmp > UDC_EPIN_NUM) {
				/* set NAK */
				reg = readl(&dev->ep[tmp].regs->ctl);
				reg |= AMD_BIT(UDC_EPCTL_SNAK);
				writel(reg, &dev->ep[tmp].regs->ctl);
				dev->ep[tmp].naking = 1;

			}
		}
	}
	/* EP0 max packet */
	if (dev->gadget.speed == USB_SPEED_FULL) {
		dev->ep[UDC_EP0IN_IX].ep.maxpacket = UDC_FS_EP0IN_MAX_PKT_SIZE;
		dev->ep[UDC_EP0OUT_IX].ep.maxpacket =
						UDC_FS_EP0OUT_MAX_PKT_SIZE;
	} else if (dev->gadget.speed == USB_SPEED_HIGH) {
		dev->ep[UDC_EP0IN_IX].ep.maxpacket = UDC_EP0IN_MAX_PKT_SIZE;
		dev->ep[UDC_EP0OUT_IX].ep.maxpacket = UDC_EP0OUT_MAX_PKT_SIZE;
	}

	/*
	 * with suspend bug workaround, ep0 params for gadget driver
	 * are set at gadget driver bind() call
	 */
	dev->gadget.ep0 = &dev->ep[UDC_EP0IN_IX].ep;
	dev->ep[UDC_EP0IN_IX].halted = 0;
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);

	/* init cfg/alt/int */
	dev->cur_config = 0;
	dev->cur_intf = 0;
	dev->cur_alt = 0;
}