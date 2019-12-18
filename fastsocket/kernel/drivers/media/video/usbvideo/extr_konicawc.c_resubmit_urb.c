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
struct uvd {int /*<<< orphan*/  dev; } ;
struct urb {int /*<<< orphan*/  transfer_buffer_length; scalar_t__ status; int /*<<< orphan*/  dev; TYPE_1__* iso_frame_desc; } ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int FRAMES_PER_DESC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resubmit_urb(struct uvd *uvd, struct urb *urb)
{
	int i, ret;
	for (i = 0; i < FRAMES_PER_DESC; i++) {
		urb->iso_frame_desc[i].status = 0;
	}
	urb->dev = uvd->dev;
	urb->status = 0;
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	DEBUG(3, "submitting urb of length %d", urb->transfer_buffer_length);
	if(ret)
		err("usb_submit_urb error (%d)", ret);

}