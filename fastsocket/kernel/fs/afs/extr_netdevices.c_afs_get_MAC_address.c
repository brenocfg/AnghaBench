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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 size_t ETH_ALEN ; 
 struct net_device* __dev_getfirstbyhwtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int afs_get_MAC_address(u8 *mac, size_t maclen)
{
	struct net_device *dev;
	int ret = -ENODEV;

	BUG_ON(maclen != ETH_ALEN);

	rtnl_lock();
	dev = __dev_getfirstbyhwtype(&init_net, ARPHRD_ETHER);
	if (dev) {
		memcpy(mac, dev->dev_addr, maclen);
		ret = 0;
	}
	rtnl_unlock();
	return ret;
}