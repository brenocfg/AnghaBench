#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbnet {TYPE_1__* net; TYPE_2__* udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int* dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int hex_to_bin (unsigned char) ; 
 int usb_string (TYPE_2__*,int,unsigned char*,int) ; 

int usbnet_get_ethernet_addr(struct usbnet *dev, int iMACAddress)
{
	int 		tmp, i;
	unsigned char	buf [13];

	tmp = usb_string(dev->udev, iMACAddress, buf, sizeof buf);
	if (tmp != 12) {
		dev_dbg(&dev->udev->dev,
			"bad MAC string %d fetch, %d\n", iMACAddress, tmp);
		if (tmp >= 0)
			tmp = -EINVAL;
		return tmp;
	}
	for (i = tmp = 0; i < 6; i++, tmp += 2)
		dev->net->dev_addr [i] =
			(hex_to_bin(buf[tmp]) << 4) + hex_to_bin(buf[tmp + 1]);
	return 0;
}