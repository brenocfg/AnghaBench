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
struct ethtool_regs {int /*<<< orphan*/  len; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcs7830_get_reg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mcs7830_get_rev (struct usbnet*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mcs7830_get_regs(struct net_device *net, struct ethtool_regs *regs, void *data)
{
	struct usbnet *dev = netdev_priv(net);

	regs->version = mcs7830_get_rev(dev);
	mcs7830_get_reg(dev, 0, regs->len, data);
}