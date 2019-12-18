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
struct sisusb_usb_data {int /*<<< orphan*/ * urbstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SU_URB_ALLOC ; 
 int sisusb_outurb_available (struct sisusb_usb_data*) ; 

__attribute__((used)) static int
sisusb_alloc_outbuf(struct sisusb_usb_data *sisusb)
{
	int i;

	i = sisusb_outurb_available(sisusb);

	if (i >= 0)
		sisusb->urbstatus[i] |= SU_URB_ALLOC;

	return i;
}