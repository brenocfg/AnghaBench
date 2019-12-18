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
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer_length; } ;
struct TYPE_2__ {int nfields; int num_bufs; struct urb** transfer_buffer; struct urb** urb; } ;
struct em28xx {TYPE_1__ isoc_ctl; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_capture_start (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_isocdbg (char*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

void em28xx_uninit_isoc(struct em28xx *dev)
{
	struct urb *urb;
	int i;

	em28xx_isocdbg("em28xx: called em28xx_uninit_isoc\n");

	dev->isoc_ctl.nfields = -1;
	for (i = 0; i < dev->isoc_ctl.num_bufs; i++) {
		urb = dev->isoc_ctl.urb[i];
		if (urb) {
			if (!irqs_disabled())
				usb_kill_urb(urb);
			else
				usb_unlink_urb(urb);

			if (dev->isoc_ctl.transfer_buffer[i]) {
				usb_buffer_free(dev->udev,
					urb->transfer_buffer_length,
					dev->isoc_ctl.transfer_buffer[i],
					urb->transfer_dma);
			}
			usb_free_urb(urb);
			dev->isoc_ctl.urb[i] = NULL;
		}
		dev->isoc_ctl.transfer_buffer[i] = NULL;
	}

	kfree(dev->isoc_ctl.urb);
	kfree(dev->isoc_ctl.transfer_buffer);

	dev->isoc_ctl.urb = NULL;
	dev->isoc_ctl.transfer_buffer = NULL;
	dev->isoc_ctl.num_bufs = 0;

	em28xx_capture_start(dev, 0);
}