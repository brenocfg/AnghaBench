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
struct TYPE_2__ {int /*<<< orphan*/ ** transfer_buffer; int /*<<< orphan*/ ** urb; } ;
struct cx231xx {TYPE_1__ adev; } ;

/* Variables and functions */
 int CX231XX_AUDIO_BUFS ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx231xx_bulk_audio_deinit(struct cx231xx *dev)
{
	int i;

	dprintk("Stopping bulk\n");

	for (i = 0; i < CX231XX_AUDIO_BUFS; i++) {
		if (dev->adev.urb[i]) {
			if (!irqs_disabled())
				usb_kill_urb(dev->adev.urb[i]);
			else
				usb_unlink_urb(dev->adev.urb[i]);

			usb_free_urb(dev->adev.urb[i]);
			dev->adev.urb[i] = NULL;

			kfree(dev->adev.transfer_buffer[i]);
			dev->adev.transfer_buffer[i] = NULL;
		}
	}

	return 0;
}