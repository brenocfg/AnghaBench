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
typedef  int u32 ;
struct usba_udc {int /*<<< orphan*/  lock; } ;
struct usba_request {int /*<<< orphan*/  queue; scalar_t__ using_dma; } ;
struct TYPE_4__ {int /*<<< orphan*/ * next; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct usba_ep {int last_dma_status; int index; TYPE_2__ queue; TYPE_1__ ep; struct usba_udc* udc; } ;
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ,struct usba_request*) ; 
 int DBG_GADGET ; 
 int DBG_QUEUE ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  EPT_RST ; 
 int /*<<< orphan*/  STATUS ; 
 int USBA_DMA_CH_EN ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_complete (struct usba_ep*,struct usba_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_dma (struct usba_ep*,int*) ; 
 int /*<<< orphan*/  submit_next_request (struct usba_ep*) ; 
 struct usba_ep* to_usba_ep (struct usb_ep*) ; 
 struct usba_request* to_usba_req (struct usb_request*) ; 
 int usba_dma_readl (struct usba_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_update_req (struct usba_ep*,struct usba_request*,int) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usba_ep_dequeue(struct usb_ep *_ep, struct usb_request *_req)
{
	struct usba_ep *ep = to_usba_ep(_ep);
	struct usba_udc *udc = ep->udc;
	struct usba_request *req = to_usba_req(_req);
	unsigned long flags;
	u32 status;

	DBG(DBG_GADGET | DBG_QUEUE, "ep_dequeue: %s, req %p\n",
			ep->ep.name, req);

	spin_lock_irqsave(&udc->lock, flags);

	if (req->using_dma) {
		/*
		 * If this request is currently being transferred,
		 * stop the DMA controller and reset the FIFO.
		 */
		if (ep->queue.next == &req->queue) {
			status = usba_dma_readl(ep, STATUS);
			if (status & USBA_DMA_CH_EN)
				stop_dma(ep, &status);

#ifdef CONFIG_USB_GADGET_DEBUG_FS
			ep->last_dma_status = status;
#endif

			usba_writel(udc, EPT_RST, 1 << ep->index);

			usba_update_req(ep, req, status);
		}
	}

	/*
	 * Errors should stop the queue from advancing until the
	 * completion function returns.
	 */
	list_del_init(&req->queue);

	request_complete(ep, req, -ECONNRESET);

	/* Process the next request if any */
	submit_next_request(ep);
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}