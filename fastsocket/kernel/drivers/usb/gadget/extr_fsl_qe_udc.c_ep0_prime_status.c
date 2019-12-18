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
struct qe_udc {int ep0_dir; int /*<<< orphan*/  ep0_state; struct qe_ep* eps; } ;
struct qe_ep {int /*<<< orphan*/  txframe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_STATE_NEED_ZLP ; 
 int NO_REQ ; 
 int SETUP_STATUS ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int /*<<< orphan*/  WAIT_FOR_OUT_STATUS ; 
 int /*<<< orphan*/  sendnulldata (struct qe_ep*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ep0_prime_status(struct qe_udc *udc, int direction)
{

	struct qe_ep *ep = &udc->eps[0];

	if (direction == USB_DIR_IN) {
		udc->ep0_state = DATA_STATE_NEED_ZLP;
		udc->ep0_dir = USB_DIR_IN;
		sendnulldata(ep, ep->txframe, SETUP_STATUS | NO_REQ);
	} else {
		udc->ep0_dir = USB_DIR_OUT;
		udc->ep0_state = WAIT_FOR_OUT_STATUS;
	}

	return 0;
}