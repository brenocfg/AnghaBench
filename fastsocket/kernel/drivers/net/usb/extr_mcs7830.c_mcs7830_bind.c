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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  phy_id; struct net_device* dev; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; } ;
struct usbnet {TYPE_1__ mii; scalar_t__ rx_urb_size; struct net_device* net; } ;
struct usb_interface {int dummy; } ;
struct net_device {scalar_t__ dev_addr; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * ethtool_ops; } ;

/* Variables and functions */
 scalar_t__ ETH_FRAME_LEN ; 
 int /*<<< orphan*/  mcs7830_ethtool_ops ; 
 int mcs7830_init_dev (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_mdio_read ; 
 int /*<<< orphan*/  mcs7830_mdio_write ; 
 int /*<<< orphan*/  mcs7830_netdev_ops ; 
 int /*<<< orphan*/  mcs7830_set_multicast (struct net_device*) ; 
 int usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int mcs7830_bind(struct usbnet *dev, struct usb_interface *udev)
{
	struct net_device *net = dev->net;
	int ret;

	ret = mcs7830_init_dev(dev);
	if (ret)
		goto out;

	net->ethtool_ops = &mcs7830_ethtool_ops;
	net->netdev_ops = &mcs7830_netdev_ops;
	mcs7830_set_multicast(net);

	/* reserve space for the status byte on rx */
	dev->rx_urb_size = ETH_FRAME_LEN + 1;

	dev->mii.mdio_read = mcs7830_mdio_read;
	dev->mii.mdio_write = mcs7830_mdio_write;
	dev->mii.dev = net;
	dev->mii.phy_id_mask = 0x3f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = *((u8 *) net->dev_addr + 1);

	ret = usbnet_get_endpoints(dev, udev);
out:
	return ret;
}