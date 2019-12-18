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
struct urb {scalar_t__ status; struct iforce* context; } ;
struct iforce {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,scalar_t__) ; 
 int /*<<< orphan*/  iforce_usb_xmit (struct iforce*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iforce_usb_out(struct urb *urb)
{
	struct iforce *iforce = urb->context;

	if (urb->status) {
		dbg("urb->status %d, exiting", urb->status);
		return;
	}

	iforce_usb_xmit(iforce);

	wake_up(&iforce->wait);
}