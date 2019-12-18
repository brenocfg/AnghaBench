#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_request {int /*<<< orphan*/  status; scalar_t__ actual; int /*<<< orphan*/  short_not_ok; int /*<<< orphan*/  zero; int /*<<< orphan*/  no_interrupt; int /*<<< orphan*/  buf; int /*<<< orphan*/  length; } ;
struct usb_ep {int /*<<< orphan*/  name; } ;
struct s3c_hsotg_req {int /*<<< orphan*/  queue; } ;
struct s3c_hsotg_ep {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; struct s3c_hsotg* parent; } ;
struct s3c_hsotg {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 struct s3c_hsotg_ep* our_ep (struct usb_ep*) ; 
 struct s3c_hsotg_req* our_req (struct usb_request*) ; 
 int s3c_hsotg_map_dma (struct s3c_hsotg*,struct s3c_hsotg_ep*,struct usb_request*) ; 
 int /*<<< orphan*/  s3c_hsotg_start_req (struct s3c_hsotg*,struct s3c_hsotg_ep*,struct s3c_hsotg_req*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ using_dma (struct s3c_hsotg*) ; 

__attribute__((used)) static int s3c_hsotg_ep_queue(struct usb_ep *ep, struct usb_request *req,
			      gfp_t gfp_flags)
{
	struct s3c_hsotg_req *hs_req = our_req(req);
	struct s3c_hsotg_ep *hs_ep = our_ep(ep);
	struct s3c_hsotg *hs = hs_ep->parent;
	unsigned long irqflags;
	bool first;

	dev_dbg(hs->dev, "%s: req %p: %d@%p, noi=%d, zero=%d, snok=%d\n",
		ep->name, req, req->length, req->buf, req->no_interrupt,
		req->zero, req->short_not_ok);

	/* initialise status of the request */
	INIT_LIST_HEAD(&hs_req->queue);
	req->actual = 0;
	req->status = -EINPROGRESS;

	/* if we're using DMA, sync the buffers as necessary */
	if (using_dma(hs)) {
		int ret = s3c_hsotg_map_dma(hs, hs_ep, req);
		if (ret)
			return ret;
	}

	spin_lock_irqsave(&hs_ep->lock, irqflags);

	first = list_empty(&hs_ep->queue);
	list_add_tail(&hs_req->queue, &hs_ep->queue);

	if (first)
		s3c_hsotg_start_req(hs, hs_ep, hs_req, false);

	spin_unlock_irqrestore(&hs_ep->lock, irqflags);

	return 0;
}