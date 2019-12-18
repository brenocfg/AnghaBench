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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct hso_shared_int {int /*<<< orphan*/  shared_intr_urb; struct hso_shared_int* shared_intr_buf; int /*<<< orphan*/  shared_int_lock; TYPE_1__* intr_endp; } ;
struct TYPE_2__ {int wMaxPacketSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_INT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* hso_get_ep (struct usb_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hso_shared_int*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct hso_shared_int *hso_create_shared_int(struct usb_interface *interface)
{
	struct hso_shared_int *mux = kzalloc(sizeof(*mux), GFP_KERNEL);

	if (!mux)
		return NULL;

	mux->intr_endp = hso_get_ep(interface, USB_ENDPOINT_XFER_INT,
				    USB_DIR_IN);
	if (!mux->intr_endp) {
		dev_err(&interface->dev, "Can't find INT IN endpoint\n");
		goto exit;
	}

	mux->shared_intr_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!mux->shared_intr_urb) {
		dev_err(&interface->dev, "Could not allocate intr urb?");
		goto exit;
	}
	mux->shared_intr_buf = kzalloc(mux->intr_endp->wMaxPacketSize,
				       GFP_KERNEL);
	if (!mux->shared_intr_buf) {
		dev_err(&interface->dev, "Could not allocate intr buf?");
		goto exit;
	}

	mutex_init(&mux->shared_int_lock);

	return mux;

exit:
	kfree(mux->shared_intr_buf);
	usb_free_urb(mux->shared_intr_urb);
	kfree(mux);
	return NULL;
}