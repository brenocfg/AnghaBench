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
struct net_device {int type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  broadcast; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  ARPHRD_ETHER 132 
#define  ARPHRD_FDDI 131 
#define  ARPHRD_IEEE802 130 
#define  ARPHRD_IEEE802_TR 129 
#define  ARPHRD_INFINIBAND 128 
 int EINVAL ; 
 int /*<<< orphan*/  ip_eth_mc_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_ib_mc_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_tr_mc_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int arp_mc_map(__be32 addr, u8 *haddr, struct net_device *dev, int dir)
{
	switch (dev->type) {
	case ARPHRD_ETHER:
	case ARPHRD_FDDI:
	case ARPHRD_IEEE802:
		ip_eth_mc_map(addr, haddr);
		return 0;
	case ARPHRD_IEEE802_TR:
		ip_tr_mc_map(addr, haddr);
		return 0;
	case ARPHRD_INFINIBAND:
		ip_ib_mc_map(addr, dev->broadcast, haddr);
		return 0;
	default:
		if (dir) {
			memcpy(haddr, dev->broadcast, dev->addr_len);
			return 0;
		}
	}
	return -EINVAL;
}