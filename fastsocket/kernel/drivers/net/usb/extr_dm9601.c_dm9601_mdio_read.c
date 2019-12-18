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
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,...) ; 
 int /*<<< orphan*/  dm_read_shared_word (struct usbnet*,int,int,int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dm9601_mdio_read(struct net_device *netdev, int phy_id, int loc)
{
	struct usbnet *dev = netdev_priv(netdev);

	__le16 res;

	if (phy_id) {
		devdbg(dev, "Only internal phy supported");
		return 0;
	}

	dm_read_shared_word(dev, 1, loc, &res);

	devdbg(dev,
	       "dm9601_mdio_read() phy_id=0x%02x, loc=0x%02x, returns=0x%04x",
	       phy_id, loc, le16_to_cpu(res));

	return le16_to_cpu(res);
}