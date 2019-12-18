#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer_length; } ;
struct TYPE_5__ {int nfields; int num_bufs; struct urb** transfer_buffer; struct urb** urb; } ;
struct TYPE_4__ {int /*<<< orphan*/ * transfer_buffer; } ;
struct TYPE_6__ {TYPE_2__ bulk_ctl; TYPE_1__ isoc_ctl; } ;
struct cx231xx {scalar_t__ mode_tv; TYPE_3__ video_mode; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Raw_Video ; 
 int /*<<< orphan*/  TS1_serial_mode ; 
 int /*<<< orphan*/  cx231xx_capture_start (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_isocdbg (char*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

void cx231xx_uninit_bulk(struct cx231xx *dev)
{
	struct urb *urb;
	int i;

	cx231xx_isocdbg("cx231xx: called cx231xx_uninit_bulk\n");

	dev->video_mode.bulk_ctl.nfields = -1;
	for (i = 0; i < dev->video_mode.bulk_ctl.num_bufs; i++) {
		urb = dev->video_mode.bulk_ctl.urb[i];
		if (urb) {
			if (!irqs_disabled())
				usb_kill_urb(urb);
			else
				usb_unlink_urb(urb);

			if (dev->video_mode.bulk_ctl.transfer_buffer[i]) {
				usb_buffer_free(dev->udev,
						urb->transfer_buffer_length,
						dev->video_mode.isoc_ctl.
						transfer_buffer[i],
						urb->transfer_dma);
			}
			usb_free_urb(urb);
			dev->video_mode.bulk_ctl.urb[i] = NULL;
		}
		dev->video_mode.bulk_ctl.transfer_buffer[i] = NULL;
	}

	kfree(dev->video_mode.bulk_ctl.urb);
	kfree(dev->video_mode.bulk_ctl.transfer_buffer);

	dev->video_mode.bulk_ctl.urb = NULL;
	dev->video_mode.bulk_ctl.transfer_buffer = NULL;
	dev->video_mode.bulk_ctl.num_bufs = 0;

	if (dev->mode_tv == 0)
		cx231xx_capture_start(dev, 0, Raw_Video);
	else
		cx231xx_capture_start(dev, 0, TS1_serial_mode);


}