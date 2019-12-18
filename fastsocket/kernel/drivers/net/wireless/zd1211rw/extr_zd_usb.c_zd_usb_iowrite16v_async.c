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
typedef  int /*<<< orphan*/  u16 ;
struct zd_usb {struct urb* urb_async_waiting; int /*<<< orphan*/  in_async; } ;
struct zd_ioreq16 {int /*<<< orphan*/  value; scalar_t__ addr; } ;
struct usb_req_write_regs {struct reg_data* reg_writes; void* id; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterval; } ;
struct usb_host_endpoint {TYPE_2__ desc; } ;
struct usb_device {int dummy; } ;
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct reg_data {void* value; void* addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EP_REGS_OUT ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 unsigned int USB_MAX_IOWRITE16_COUNT ; 
 int /*<<< orphan*/  USB_REQ_WRITE_REGS ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  iowrite16v_urb_complete ; 
 struct usb_req_write_regs* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_xfer_int (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,struct usb_req_write_regs*,int,int /*<<< orphan*/ ,struct zd_usb*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,struct usb_req_write_regs*,int,int /*<<< orphan*/ ,struct zd_usb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct usb_host_endpoint* usb_pipe_endpoint (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int zd_submit_waiting_urb (struct zd_usb*,int) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 TYPE_1__* zd_usb_to_chip (struct zd_usb*) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

int zd_usb_iowrite16v_async(struct zd_usb *usb, const struct zd_ioreq16 *ioreqs,
			    unsigned int count)
{
	int r;
	struct usb_device *udev;
	struct usb_req_write_regs *req = NULL;
	int i, req_len;
	struct urb *urb;
	struct usb_host_endpoint *ep;

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));
	ZD_ASSERT(usb->in_async);

	if (count == 0)
		return 0;
	if (count > USB_MAX_IOWRITE16_COUNT) {
		dev_dbg_f(zd_usb_dev(usb),
			"error: count %u exceeds possible max %u\n",
			count, USB_MAX_IOWRITE16_COUNT);
		return -EINVAL;
	}
	if (in_atomic()) {
		dev_dbg_f(zd_usb_dev(usb),
			"error: io in atomic context not supported\n");
		return -EWOULDBLOCK;
	}

	udev = zd_usb_to_usbdev(usb);

	ep = usb_pipe_endpoint(udev, usb_sndintpipe(udev, EP_REGS_OUT));
	if (!ep)
		return -ENOENT;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return -ENOMEM;

	req_len = sizeof(struct usb_req_write_regs) +
		  count * sizeof(struct reg_data);
	req = kmalloc(req_len, GFP_KERNEL);
	if (!req) {
		r = -ENOMEM;
		goto error;
	}

	req->id = cpu_to_le16(USB_REQ_WRITE_REGS);
	for (i = 0; i < count; i++) {
		struct reg_data *rw  = &req->reg_writes[i];
		rw->addr = cpu_to_le16((u16)ioreqs[i].addr);
		rw->value = cpu_to_le16(ioreqs[i].value);
	}

	/* In USB 2.0 mode endpoint is interrupt type. However in USB 1.1 mode
	 * endpoint is bulk. Select correct type URB by endpoint descriptor.
	 */
	if (usb_endpoint_xfer_int(&ep->desc))
		usb_fill_int_urb(urb, udev, usb_sndintpipe(udev, EP_REGS_OUT),
				 req, req_len, iowrite16v_urb_complete, usb,
				 ep->desc.bInterval);
	else
		usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, EP_REGS_OUT),
				  req, req_len, iowrite16v_urb_complete, usb);

	urb->transfer_flags |= URB_FREE_BUFFER;

	/* Submit previous URB */
	r = zd_submit_waiting_urb(usb, false);
	if (r) {
		dev_dbg_f(zd_usb_dev(usb),
			"error in zd_submit_waiting_usb(). "
			"Error number %d\n", r);
		goto error;
	}

	/* Delay submit so that URB_NO_INTERRUPT flag can be set for all URBs
	 * of currect batch except for very last.
	 */
	usb->urb_async_waiting = urb;
	return 0;
error:
	usb_free_urb(urb);
	return r;
}