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
typedef  int u16 ;
struct usb_request {int length; scalar_t__ zero; int /*<<< orphan*/  complete; int /*<<< orphan*/ * buf; } ;
struct usb_ep {struct dev_data* driver_data; } ;
struct dev_data {int /*<<< orphan*/ * rbuf; scalar_t__ setup_out_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct dev_data*,char*) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ep0_complete ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_req (struct usb_ep *ep, struct usb_request *req, u16 len)
{
	struct dev_data	*dev = ep->driver_data;

	if (dev->setup_out_ready) {
		DBG (dev, "ep0 request busy!\n");
		return -EBUSY;
	}
	if (len > sizeof (dev->rbuf))
		req->buf = kmalloc(len, GFP_ATOMIC);
	if (req->buf == NULL) {
		req->buf = dev->rbuf;
		return -ENOMEM;
	}
	req->complete = ep0_complete;
	req->length = len;
	req->zero = 0;
	return 0;
}