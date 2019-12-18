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
struct uvd {int /*<<< orphan*/  dev; } ;
struct urb {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resubmit_urb(struct uvd *uvd, struct urb *urb)
{
	int ret;

	urb->dev = uvd->dev;
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	if (ret)
		err("usb_submit_urb error (%d)", ret);
}