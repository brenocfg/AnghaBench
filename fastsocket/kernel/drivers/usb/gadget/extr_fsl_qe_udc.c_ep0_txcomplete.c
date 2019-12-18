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
struct TYPE_3__ {scalar_t__ length; unsigned int actual; } ;
struct qe_req {TYPE_1__ req; } ;
struct qe_frame {int dummy; } ;
struct qe_ep {int last; scalar_t__ sent; TYPE_2__* udc; struct qe_req* tx_req; struct qe_frame* txframe; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  ep0_state; } ;

/* Variables and functions */
 int NO_REQ ; 
 int SETUP_STATUS ; 
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int ZLP ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ep0_req_complete (TYPE_2__*,struct qe_req*) ; 
 int frame_get_info (struct qe_frame*) ; 
 int /*<<< orphan*/  sendnulldata (struct qe_ep*,struct qe_frame*,int) ; 

__attribute__((used)) static int ep0_txcomplete(struct qe_ep *ep, unsigned char restart)
{
	struct qe_req *tx_req = NULL;
	struct qe_frame *frame = ep->txframe;

	if ((frame_get_info(frame) & (ZLP | NO_REQ)) == (ZLP | NO_REQ)) {
		if (!restart)
			ep->udc->ep0_state = WAIT_FOR_SETUP;
		else
			sendnulldata(ep, ep->txframe, SETUP_STATUS | NO_REQ);
		return 0;
	}

	tx_req = ep->tx_req;
	if (tx_req != NULL) {
		if (!restart) {
			int asent = ep->last;
			ep->sent += asent;
			ep->last -= asent;
		} else {
			ep->last = 0;
		}

		/* a request already were transmitted completely */
		if ((ep->tx_req->req.length - ep->sent) <= 0) {
			ep->tx_req->req.actual = (unsigned int)ep->sent;
			ep0_req_complete(ep->udc, ep->tx_req);
			ep->tx_req = NULL;
			ep->last = 0;
			ep->sent = 0;
		}
	} else {
		dev_vdbg(ep->udc->dev, "the ep0_controller have no req\n");
	}

	return 0;
}