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
struct net_device {int type; } ;

/* Variables and functions */
#define  ARPHRD_ARCNET 133 
#define  ARPHRD_ETHER 132 
#define  ARPHRD_FDDI 131 
#define  ARPHRD_IEEE802_TR 130 
#define  ARPHRD_INFINIBAND 129 
#define  ARPHRD_SIT 128 
 int addrconf_ifid_arcnet (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_eui48 (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_infiniband (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_sit (int /*<<< orphan*/ *,struct net_device*) ; 

__attribute__((used)) static int ipv6_generate_eui64(u8 *eui, struct net_device *dev)
{
	switch (dev->type) {
	case ARPHRD_ETHER:
	case ARPHRD_FDDI:
	case ARPHRD_IEEE802_TR:
		return addrconf_ifid_eui48(eui, dev);
	case ARPHRD_ARCNET:
		return addrconf_ifid_arcnet(eui, dev);
	case ARPHRD_INFINIBAND:
		return addrconf_ifid_infiniband(eui, dev);
	case ARPHRD_SIT:
		return addrconf_ifid_sit(eui, dev);
	}
	return -1;
}