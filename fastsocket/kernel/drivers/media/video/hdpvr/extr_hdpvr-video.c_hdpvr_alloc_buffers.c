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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
struct urb {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct hdpvr_device {int /*<<< orphan*/  free_buff_list; int /*<<< orphan*/  bulk_in_size; int /*<<< orphan*/  bulk_in_endpointAddr; int /*<<< orphan*/  udev; int /*<<< orphan*/  v4l2_dev; } ;
struct hdpvr_buffer {int /*<<< orphan*/  buff_list; int /*<<< orphan*/  status; struct urb* urb; struct hdpvr_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSTAT_AVAILABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  hdpvr_debug ; 
 int /*<<< orphan*/  hdpvr_free_buffers (struct hdpvr_device*) ; 
 int /*<<< orphan*/  hdpvr_read_bulk_callback ; 
 int /*<<< orphan*/  kfree (struct hdpvr_buffer*) ; 
 struct hdpvr_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usb_buffer_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hdpvr_buffer*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

int hdpvr_alloc_buffers(struct hdpvr_device *dev, uint count)
{
	uint i;
	int retval = -ENOMEM;
	u8 *mem;
	struct hdpvr_buffer *buf;
	struct urb *urb;

	v4l2_dbg(MSG_INFO, hdpvr_debug, &dev->v4l2_dev,
		 "allocating %u buffers\n", count);

	for (i = 0; i < count; i++) {

		buf = kzalloc(sizeof(struct hdpvr_buffer), GFP_KERNEL);
		if (!buf) {
			v4l2_err(&dev->v4l2_dev, "cannot allocate buffer\n");
			goto exit;
		}
		buf->dev = dev;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			v4l2_err(&dev->v4l2_dev, "cannot allocate urb\n");
			goto exit_urb;
		}
		buf->urb = urb;

		mem = usb_buffer_alloc(dev->udev, dev->bulk_in_size, GFP_KERNEL,
					 &urb->transfer_dma);
		if (!mem) {
			v4l2_err(&dev->v4l2_dev,
				 "cannot allocate usb transfer buffer\n");
			goto exit_urb_buffer;
		}

		usb_fill_bulk_urb(buf->urb, dev->udev,
				  usb_rcvbulkpipe(dev->udev,
						  dev->bulk_in_endpointAddr),
				  mem, dev->bulk_in_size,
				  hdpvr_read_bulk_callback, buf);

		buf->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		buf->status = BUFSTAT_AVAILABLE;
		list_add_tail(&buf->buff_list, &dev->free_buff_list);
	}
	return 0;
exit_urb_buffer:
	usb_free_urb(urb);
exit_urb:
	kfree(buf);
exit:
	hdpvr_free_buffers(dev);
	return retval;
}