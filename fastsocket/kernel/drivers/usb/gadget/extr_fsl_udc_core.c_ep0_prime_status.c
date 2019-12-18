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
struct fsl_udc {int /*<<< orphan*/  ep0_state; struct fsl_ep* eps; int /*<<< orphan*/  ep0_dir; struct fsl_req* status_req; } ;
struct TYPE_2__ {int /*<<< orphan*/ * complete; scalar_t__ actual; int /*<<< orphan*/  status; scalar_t__ length; } ;
struct fsl_req {int /*<<< orphan*/  queue; scalar_t__ dtd_count; TYPE_1__ req; struct fsl_ep* ep; } ;
struct fsl_ep {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int ENOMEM ; 
 int EP_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  WAIT_FOR_OUT_STATUS ; 
 int /*<<< orphan*/  fsl_queue_td (struct fsl_ep*,struct fsl_req*) ; 
 scalar_t__ fsl_req_to_dtd (struct fsl_req*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ep0_prime_status(struct fsl_udc *udc, int direction)
{
	struct fsl_req *req = udc->status_req;
	struct fsl_ep *ep;

	if (direction == EP_DIR_IN)
		udc->ep0_dir = USB_DIR_IN;
	else
		udc->ep0_dir = USB_DIR_OUT;

	ep = &udc->eps[0];
	udc->ep0_state = WAIT_FOR_OUT_STATUS;

	req->ep = ep;
	req->req.length = 0;
	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	req->req.complete = NULL;
	req->dtd_count = 0;

	if (fsl_req_to_dtd(req) == 0)
		fsl_queue_td(ep, req);
	else
		return -ENOMEM;

	list_add_tail(&req->queue, &ep->queue);

	return 0;
}