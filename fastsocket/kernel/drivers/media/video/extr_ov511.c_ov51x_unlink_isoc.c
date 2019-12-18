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
struct usb_ov511 {TYPE_1__* sbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int OV511_NUMSBUF ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ov51x_unlink_isoc(struct usb_ov511 *ov)
{
	int n;

	/* Unschedule all of the iso td's */
	for (n = OV511_NUMSBUF - 1; n >= 0; n--) {
		if (ov->sbuf[n].urb) {
			usb_kill_urb(ov->sbuf[n].urb);
			usb_free_urb(ov->sbuf[n].urb);
			ov->sbuf[n].urb = NULL;
		}
	}
}