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
struct sisusb_usb_data {int numobufs; int* urbstatus; int /*<<< orphan*/ * sisurbout; } ;

/* Variables and functions */
 int SU_URB_BUSY ; 
 scalar_t__ sisusb_all_free (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sisusb_kill_all_busy(struct sisusb_usb_data *sisusb)
{
	int i;

	if (sisusb_all_free(sisusb))
		return;

	for (i = 0; i < sisusb->numobufs; i++) {

		if (sisusb->urbstatus[i] & SU_URB_BUSY)
			usb_kill_urb(sisusb->sisurbout[i]);

	}
}