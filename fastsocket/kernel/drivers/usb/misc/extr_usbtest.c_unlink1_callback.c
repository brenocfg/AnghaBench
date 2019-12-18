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
struct urb {int status; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlink1_callback (struct urb *urb)
{
	int	status = urb->status;

	// we "know" -EPIPE (stall) never happens
	if (!status)
		status = usb_submit_urb (urb, GFP_ATOMIC);
	if (status) {
		urb->status = status;
		complete(urb->context);
	}
}