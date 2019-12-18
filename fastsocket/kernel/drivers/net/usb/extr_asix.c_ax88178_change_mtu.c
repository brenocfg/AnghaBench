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
struct usbnet {int maxpacket; int hard_mtu; } ;
struct net_device {int hard_header_len; int mtu; } ;

/* Variables and functions */
 int EDOM ; 
 int EINVAL ; 
 int /*<<< orphan*/  ax88178_set_mfb (struct usbnet*) ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ax88178_change_mtu(struct net_device *net, int new_mtu)
{
	struct usbnet *dev = netdev_priv(net);
	int ll_mtu = new_mtu + net->hard_header_len + 4;

	devdbg(dev, "ax88178_change_mtu() new_mtu=%d", new_mtu);

	if (new_mtu <= 0 || ll_mtu > 16384)
		return -EINVAL;

	if ((ll_mtu % dev->maxpacket) == 0)
		return -EDOM;

	net->mtu = new_mtu;
	dev->hard_mtu = net->mtu + net->hard_header_len;
	ax88178_set_mfb(dev);

	return 0;
}