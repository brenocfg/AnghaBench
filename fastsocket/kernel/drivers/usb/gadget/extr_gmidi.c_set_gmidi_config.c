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
struct usb_request {int /*<<< orphan*/  complete; } ;
struct usb_ep {int /*<<< orphan*/  name; struct gmidi_device* driver_data; } ;
struct gmidi_device {struct usb_ep* out_ep; struct usb_ep* in_ep; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct gmidi_device*,char*,int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (struct gmidi_device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct usb_request* alloc_ep_req (struct usb_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buflen ; 
 int /*<<< orphan*/  bulk_in_desc ; 
 int /*<<< orphan*/  bulk_out_desc ; 
 int /*<<< orphan*/  gmidi_complete ; 
 unsigned int qlen ; 
 int usb_ep_enable (struct usb_ep*,int /*<<< orphan*/ *) ; 
 int usb_ep_queue (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_gmidi_config(struct gmidi_device *dev, gfp_t gfp_flags)
{
	int err = 0;
	struct usb_request *req;
	struct usb_ep *ep;
	unsigned i;

	err = usb_ep_enable(dev->in_ep, &bulk_in_desc);
	if (err) {
		ERROR(dev, "can't start %s: %d\n", dev->in_ep->name, err);
		goto fail;
	}
	dev->in_ep->driver_data = dev;

	err = usb_ep_enable(dev->out_ep, &bulk_out_desc);
	if (err) {
		ERROR(dev, "can't start %s: %d\n", dev->out_ep->name, err);
		goto fail;
	}
	dev->out_ep->driver_data = dev;

	/* allocate a bunch of read buffers and queue them all at once. */
	ep = dev->out_ep;
	for (i = 0; i < qlen && err == 0; i++) {
		req = alloc_ep_req(ep, buflen);
		if (req) {
			req->complete = gmidi_complete;
			err = usb_ep_queue(ep, req, GFP_ATOMIC);
			if (err) {
				DBG(dev, "%s queue req: %d\n", ep->name, err);
			}
		} else {
			err = -ENOMEM;
		}
	}
fail:
	/* caller is responsible for cleanup on error */
	return err;
}