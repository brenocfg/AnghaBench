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
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ speed; } ;
struct usba_udc {int /*<<< orphan*/  lock; TYPE_2__* pdev; TYPE_3__ gadget; TYPE_1__* driver; } ;
struct usba_ep {int /*<<< orphan*/  state; int /*<<< orphan*/ * desc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disconnect ) (TYPE_3__*) ;int /*<<< orphan*/  (* resume ) (TYPE_3__*) ;int /*<<< orphan*/  (* suspend ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BK_NUMBER ; 
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  CTL_ENB ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DBG_BUS ; 
 int /*<<< orphan*/  DBG_INT ; 
 int /*<<< orphan*/  DMA_INT ; 
 int EP0_EPT_SIZE ; 
 int /*<<< orphan*/  EPT_INT ; 
 int /*<<< orphan*/  EPT_SIZE ; 
 int /*<<< orphan*/  EPT_TYPE ; 
 int /*<<< orphan*/  INT_CLR ; 
 int /*<<< orphan*/  INT_ENB ; 
 int /*<<< orphan*/  INT_STA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int USBA_BF (int /*<<< orphan*/ ,int) ; 
 int USBA_BFEXT (int /*<<< orphan*/ ,int) ; 
 int USBA_BK_NUMBER_ONE ; 
 int USBA_DET_SUSPEND ; 
 int USBA_END_OF_RESET ; 
 int USBA_END_OF_RESUME ; 
 int USBA_EPT_ENABLE ; 
 int USBA_EPT_MAPPED ; 
 int USBA_EPT_TYPE_CONTROL ; 
 int USBA_HIGH_SPEED ; 
 int USBA_NR_ENDPOINTS ; 
 int USBA_RX_SETUP ; 
 int USBA_WAKE_UP ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ep_is_control (struct usba_ep*) ; 
 int /*<<< orphan*/  reset_all_endpoints (struct usba_udc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  toggle_bias (int) ; 
 int /*<<< orphan*/  usba_control_irq (struct usba_udc*,struct usba_ep*) ; 
 int /*<<< orphan*/  usba_dma_irq (struct usba_udc*,struct usba_ep*) ; 
 struct usba_ep* usba_ep ; 
 int /*<<< orphan*/  usba_ep0_desc ; 
 int /*<<< orphan*/  usba_ep_irq (struct usba_udc*,struct usba_ep*) ; 
 int usba_ep_readl (struct usba_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_ep_writel (struct usba_ep*,int /*<<< orphan*/ ,int) ; 
 int usba_readl (struct usba_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t usba_udc_irq(int irq, void *devid)
{
	struct usba_udc *udc = devid;
	u32 status;
	u32 dma_status;
	u32 ep_status;

	spin_lock(&udc->lock);

	status = usba_readl(udc, INT_STA);
	DBG(DBG_INT, "irq, status=%#08x\n", status);

	if (status & USBA_DET_SUSPEND) {
		toggle_bias(0);
		usba_writel(udc, INT_CLR, USBA_DET_SUSPEND);
		DBG(DBG_BUS, "Suspend detected\n");
		if (udc->gadget.speed != USB_SPEED_UNKNOWN
				&& udc->driver && udc->driver->suspend) {
			spin_unlock(&udc->lock);
			udc->driver->suspend(&udc->gadget);
			spin_lock(&udc->lock);
		}
	}

	if (status & USBA_WAKE_UP) {
		toggle_bias(1);
		usba_writel(udc, INT_CLR, USBA_WAKE_UP);
		DBG(DBG_BUS, "Wake Up CPU detected\n");
	}

	if (status & USBA_END_OF_RESUME) {
		usba_writel(udc, INT_CLR, USBA_END_OF_RESUME);
		DBG(DBG_BUS, "Resume detected\n");
		if (udc->gadget.speed != USB_SPEED_UNKNOWN
				&& udc->driver && udc->driver->resume) {
			spin_unlock(&udc->lock);
			udc->driver->resume(&udc->gadget);
			spin_lock(&udc->lock);
		}
	}

	dma_status = USBA_BFEXT(DMA_INT, status);
	if (dma_status) {
		int i;

		for (i = 1; i < USBA_NR_ENDPOINTS; i++)
			if (dma_status & (1 << i))
				usba_dma_irq(udc, &usba_ep[i]);
	}

	ep_status = USBA_BFEXT(EPT_INT, status);
	if (ep_status) {
		int i;

		for (i = 0; i < USBA_NR_ENDPOINTS; i++)
			if (ep_status & (1 << i)) {
				if (ep_is_control(&usba_ep[i]))
					usba_control_irq(udc, &usba_ep[i]);
				else
					usba_ep_irq(udc, &usba_ep[i]);
			}
	}

	if (status & USBA_END_OF_RESET) {
		struct usba_ep *ep0;

		usba_writel(udc, INT_CLR, USBA_END_OF_RESET);
		reset_all_endpoints(udc);

		if (udc->gadget.speed != USB_SPEED_UNKNOWN
				&& udc->driver->disconnect) {
			udc->gadget.speed = USB_SPEED_UNKNOWN;
			spin_unlock(&udc->lock);
			udc->driver->disconnect(&udc->gadget);
			spin_lock(&udc->lock);
		}

		if (status & USBA_HIGH_SPEED) {
			DBG(DBG_BUS, "High-speed bus reset detected\n");
			udc->gadget.speed = USB_SPEED_HIGH;
		} else {
			DBG(DBG_BUS, "Full-speed bus reset detected\n");
			udc->gadget.speed = USB_SPEED_FULL;
		}

		ep0 = &usba_ep[0];
		ep0->desc = &usba_ep0_desc;
		ep0->state = WAIT_FOR_SETUP;
		usba_ep_writel(ep0, CFG,
				(USBA_BF(EPT_SIZE, EP0_EPT_SIZE)
				| USBA_BF(EPT_TYPE, USBA_EPT_TYPE_CONTROL)
				| USBA_BF(BK_NUMBER, USBA_BK_NUMBER_ONE)));
		usba_ep_writel(ep0, CTL_ENB,
				USBA_EPT_ENABLE | USBA_RX_SETUP);
		usba_writel(udc, INT_ENB,
				(usba_readl(udc, INT_ENB)
				| USBA_BF(EPT_INT, 1)
				| USBA_DET_SUSPEND
				| USBA_END_OF_RESUME));

		/*
		 * Unclear why we hit this irregularly, e.g. in usbtest,
		 * but it's clearly harmless...
		 */
		if (!(usba_ep_readl(ep0, CFG) & USBA_EPT_MAPPED))
			dev_dbg(&udc->pdev->dev,
				 "ODD: EP0 configuration is invalid!\n");
	}

	spin_unlock(&udc->lock);

	return IRQ_HANDLED;
}