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
struct usb_request {int /*<<< orphan*/  (* complete ) (struct usb_ep*,struct usb_request*) ;int /*<<< orphan*/  status; scalar_t__ length; scalar_t__ actual; struct dummy* context; int /*<<< orphan*/  buf; } ;
struct usb_ep {int /*<<< orphan*/  name; } ;
struct dummy_request {int /*<<< orphan*/  queue; struct usb_request req; } ;
struct dummy_ep {int /*<<< orphan*/  queue; TYPE_1__* desc; } ;
struct dummy {int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo_buf; struct dummy_request fifo_req; int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 int ESHUTDOWN ; 
 scalar_t__ FIFO_SIZE ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct dummy_ep*,struct usb_request*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0name ; 
 struct dummy* ep_to_dummy (struct dummy_ep*) ; 
 int /*<<< orphan*/  fifo_complete (struct usb_ep*,struct usb_request*) ; 
 int /*<<< orphan*/  is_enabled (struct dummy*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct usb_ep*,struct usb_request*) ; 
 int /*<<< orphan*/  udc_dev (struct dummy*) ; 
 struct dummy_ep* usb_ep_to_dummy_ep (struct usb_ep*) ; 
 struct dummy_request* usb_request_to_dummy_request (struct usb_request*) ; 

__attribute__((used)) static int
dummy_queue (struct usb_ep *_ep, struct usb_request *_req,
		gfp_t mem_flags)
{
	struct dummy_ep		*ep;
	struct dummy_request	*req;
	struct dummy		*dum;
	unsigned long		flags;

	req = usb_request_to_dummy_request (_req);
	if (!_req || !list_empty (&req->queue) || !_req->complete)
		return -EINVAL;

	ep = usb_ep_to_dummy_ep (_ep);
	if (!_ep || (!ep->desc && _ep->name != ep0name))
		return -EINVAL;

	dum = ep_to_dummy (ep);
	if (!dum->driver || !is_enabled (dum))
		return -ESHUTDOWN;

#if 0
	dev_dbg (udc_dev(dum), "ep %p queue req %p to %s, len %d buf %p\n",
			ep, _req, _ep->name, _req->length, _req->buf);
#endif

	_req->status = -EINPROGRESS;
	_req->actual = 0;
	spin_lock_irqsave (&dum->lock, flags);

	/* implement an emulated single-request FIFO */
	if (ep->desc && (ep->desc->bEndpointAddress & USB_DIR_IN) &&
			list_empty (&dum->fifo_req.queue) &&
			list_empty (&ep->queue) &&
			_req->length <= FIFO_SIZE) {
		req = &dum->fifo_req;
		req->req = *_req;
		req->req.buf = dum->fifo_buf;
		memcpy (dum->fifo_buf, _req->buf, _req->length);
		req->req.context = dum;
		req->req.complete = fifo_complete;

		list_add_tail(&req->queue, &ep->queue);
		spin_unlock (&dum->lock);
		_req->actual = _req->length;
		_req->status = 0;
		_req->complete (_ep, _req);
		spin_lock (&dum->lock);
	}  else
		list_add_tail(&req->queue, &ep->queue);
	spin_unlock_irqrestore (&dum->lock, flags);

	/* real hardware would likely enable transfers here, in case
	 * it'd been left NAKing.
	 */
	return 0;
}