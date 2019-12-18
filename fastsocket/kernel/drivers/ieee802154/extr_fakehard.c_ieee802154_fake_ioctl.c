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
typedef  void* u16 ;
struct TYPE_2__ {void* short_addr; void* pan_id; int /*<<< orphan*/  addr_type; } ;
struct sockaddr_ieee802154 {TYPE_1__ addr; int /*<<< orphan*/  family; } ;
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IEEE802154 ; 
 int EADDRNOTAVAIL ; 
 int ENOIOCTLCMD ; 
 void* IEEE802154_ADDR_BROADCAST ; 
 int /*<<< orphan*/  IEEE802154_ADDR_SHORT ; 
 void* IEEE802154_PANID_BROADCAST ; 
#define  SIOCGIFADDR 128 
 void* fake_get_pan_id (struct net_device*) ; 
 void* fake_get_short_addr (struct net_device*) ; 

__attribute__((used)) static int ieee802154_fake_ioctl(struct net_device *dev, struct ifreq *ifr,
		int cmd)
{
	struct sockaddr_ieee802154 *sa =
		(struct sockaddr_ieee802154 *)&ifr->ifr_addr;
	u16 pan_id, short_addr;

	switch (cmd) {
	case SIOCGIFADDR:
		/* FIXME: fixed here, get from device IRL */
		pan_id = fake_get_pan_id(dev);
		short_addr = fake_get_short_addr(dev);
		if (pan_id == IEEE802154_PANID_BROADCAST ||
		    short_addr == IEEE802154_ADDR_BROADCAST)
			return -EADDRNOTAVAIL;

		sa->family = AF_IEEE802154;
		sa->addr.addr_type = IEEE802154_ADDR_SHORT;
		sa->addr.pan_id = pan_id;
		sa->addr.short_addr = short_addr;
		return 0;
	}
	return -ENOIOCTLCMD;
}