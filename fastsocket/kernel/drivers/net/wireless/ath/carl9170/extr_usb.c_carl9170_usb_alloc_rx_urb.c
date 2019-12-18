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
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_size; } ;
struct ar9170 {TYPE_1__ fw; int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_USB_EP_RX ; 
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 int /*<<< orphan*/  carl9170_usb_rx_complete ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ar9170*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct urb *carl9170_usb_alloc_rx_urb(struct ar9170 *ar, gfp_t gfp)
{
	struct urb *urb;
	void *buf;

	buf = kmalloc(ar->fw.rx_size, gfp);
	if (!buf)
		return NULL;

	urb = usb_alloc_urb(0, gfp);
	if (!urb) {
		kfree(buf);
		return NULL;
	}

	usb_fill_bulk_urb(urb, ar->udev, usb_rcvbulkpipe(ar->udev,
			  AR9170_USB_EP_RX), buf, ar->fw.rx_size,
			  carl9170_usb_rx_complete, ar);

	urb->transfer_flags |= URB_FREE_BUFFER;

	return urb;
}