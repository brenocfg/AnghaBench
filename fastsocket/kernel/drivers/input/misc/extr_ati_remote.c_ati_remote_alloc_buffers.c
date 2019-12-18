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
struct usb_device {int dummy; } ;
struct ati_remote {void* out_urb; void* irq_urb; void* outbuf; int /*<<< orphan*/  outbuf_dma; void* inbuf; int /*<<< orphan*/  inbuf_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_BUFSIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_buffer_alloc (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ati_remote_alloc_buffers(struct usb_device *udev,
				    struct ati_remote *ati_remote)
{
	ati_remote->inbuf = usb_buffer_alloc(udev, DATA_BUFSIZE, GFP_ATOMIC,
					     &ati_remote->inbuf_dma);
	if (!ati_remote->inbuf)
		return -1;

	ati_remote->outbuf = usb_buffer_alloc(udev, DATA_BUFSIZE, GFP_ATOMIC,
					      &ati_remote->outbuf_dma);
	if (!ati_remote->outbuf)
		return -1;

	ati_remote->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!ati_remote->irq_urb)
		return -1;

	ati_remote->out_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!ati_remote->out_urb)
		return -1;

	return 0;
}