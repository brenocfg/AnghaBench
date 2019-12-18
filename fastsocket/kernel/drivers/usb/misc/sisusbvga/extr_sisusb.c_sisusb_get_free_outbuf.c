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
struct sisusb_usb_data {int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 int HZ ; 
 int sisusb_outurb_available (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
sisusb_get_free_outbuf(struct sisusb_usb_data *sisusb)
{
	int i, timeout = 5 * HZ;

	wait_event_timeout(sisusb->wait_q,
				((i = sisusb_outurb_available(sisusb)) >= 0),
				timeout);

	return i;
}