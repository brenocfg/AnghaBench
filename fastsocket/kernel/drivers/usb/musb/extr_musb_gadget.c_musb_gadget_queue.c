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
struct usb_request {int /*<<< orphan*/  buf; } ;
struct usb_ep {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ dma; int /*<<< orphan*/  list; int /*<<< orphan*/  length; int /*<<< orphan*/  buf; int /*<<< orphan*/  status; scalar_t__ actual; } ;
struct musb_request {int mapped; TYPE_1__ request; scalar_t__ tx; int /*<<< orphan*/  epnum; struct musb_ep* ep; struct musb* musb; } ;
struct TYPE_4__ {int /*<<< orphan*/ * next; } ;
struct musb_ep {TYPE_2__ req_list; int /*<<< orphan*/  busy; int /*<<< orphan*/  desc; scalar_t__ dma; scalar_t__ is_in; int /*<<< orphan*/  current_epnum; struct musb* musb; } ;
struct musb {int /*<<< orphan*/  lock; int /*<<< orphan*/  controller; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,struct usb_request*,struct usb_request*,...) ; 
 scalar_t__ DMA_ADDR_INVALID ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 int ENODATA ; 
 int ESHUTDOWN ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dma_capable () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  musb_ep_restart (struct musb*,struct musb_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct musb_ep* to_musb_ep (struct usb_ep*) ; 
 struct musb_request* to_musb_request (struct usb_request*) ; 

__attribute__((used)) static int musb_gadget_queue(struct usb_ep *ep, struct usb_request *req,
			gfp_t gfp_flags)
{
	struct musb_ep		*musb_ep;
	struct musb_request	*request;
	struct musb		*musb;
	int			status = 0;
	unsigned long		lockflags;

	if (!ep || !req)
		return -EINVAL;
	if (!req->buf)
		return -ENODATA;

	musb_ep = to_musb_ep(ep);
	musb = musb_ep->musb;

	request = to_musb_request(req);
	request->musb = musb;

	if (request->ep != musb_ep)
		return -EINVAL;

	DBG(4, "<== to %s request=%p\n", ep->name, req);

	/* request is mine now... */
	request->request.actual = 0;
	request->request.status = -EINPROGRESS;
	request->epnum = musb_ep->current_epnum;
	request->tx = musb_ep->is_in;

	if (is_dma_capable() && musb_ep->dma) {
		if (request->request.dma == DMA_ADDR_INVALID) {
			request->request.dma = dma_map_single(
					musb->controller,
					request->request.buf,
					request->request.length,
					request->tx
						? DMA_TO_DEVICE
						: DMA_FROM_DEVICE);
			request->mapped = 1;
		} else {
			dma_sync_single_for_device(musb->controller,
					request->request.dma,
					request->request.length,
					request->tx
						? DMA_TO_DEVICE
						: DMA_FROM_DEVICE);
			request->mapped = 0;
		}
	} else if (!req->buf) {
		return -ENODATA;
	} else
		request->mapped = 0;

	spin_lock_irqsave(&musb->lock, lockflags);

	/* don't queue if the ep is down */
	if (!musb_ep->desc) {
		DBG(4, "req %p queued to %s while ep %s\n",
				req, ep->name, "disabled");
		status = -ESHUTDOWN;
		goto cleanup;
	}

	/* add request to the list */
	list_add_tail(&(request->request.list), &(musb_ep->req_list));

	/* it this is the head of the queue, start i/o ... */
	if (!musb_ep->busy && &request->request.list == musb_ep->req_list.next)
		musb_ep_restart(musb, request);

cleanup:
	spin_unlock_irqrestore(&musb->lock, lockflags);
	return status;
}