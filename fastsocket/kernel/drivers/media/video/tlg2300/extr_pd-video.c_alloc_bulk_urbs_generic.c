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
typedef  int /*<<< orphan*/  usb_complete_t ;
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {int dummy; } ;
struct urb {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_buffer_alloc (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int alloc_bulk_urbs_generic(struct urb **urb_array, int num,
			struct usb_device *udev, u8 ep_addr,
			int buf_size, gfp_t gfp_flags,
			usb_complete_t complete_fn, void *context)
{
	int i = 0;

	for (; i < num; i++) {
		void *mem;
		struct urb *urb = usb_alloc_urb(0, gfp_flags);
		if (urb == NULL)
			return i;

		mem = usb_buffer_alloc(udev, buf_size, gfp_flags,
					 &urb->transfer_dma);
		if (mem == NULL) {
			usb_free_urb(urb);
			return i;
		}

		usb_fill_bulk_urb(urb, udev, usb_rcvbulkpipe(udev, ep_addr),
				mem, buf_size, complete_fn, context);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		urb_array[i] = urb;
	}
	return i;
}