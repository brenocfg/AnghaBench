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
struct usb_device {int maxchild; } ;

/* Variables and functions */
 int find_port_owner (struct usb_device*,int,void***) ; 

void usb_hub_release_all_ports(struct usb_device *hdev, void *owner)
{
	int n;
	void **powner;

	n = find_port_owner(hdev, 1, &powner);
	if (n == 0) {
		for (; n < hdev->maxchild; (++n, ++powner)) {
			if (*powner == owner)
				*powner = NULL;
		}
	}
}