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
struct sisusb_usb_data {int /*<<< orphan*/ * sisurbin; int /*<<< orphan*/ ** sisurbout; } ;

/* Variables and functions */
 int NUMOBUFS ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sisusb_free_urbs(struct sisusb_usb_data *sisusb)
{
	int i;

	for (i = 0; i < NUMOBUFS; i++) {
		usb_free_urb(sisusb->sisurbout[i]);
		sisusb->sisurbout[i] = NULL;
	}
	usb_free_urb(sisusb->sisurbin);
	sisusb->sisurbin = NULL;
}