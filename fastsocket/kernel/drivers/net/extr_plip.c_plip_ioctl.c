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
struct plipconf {int pcmd; int /*<<< orphan*/  nibble; int /*<<< orphan*/  trigger; } ;
struct net_local {int /*<<< orphan*/  nibble; int /*<<< orphan*/  trigger; } ;
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_ifru; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  PLIP_GET_TIMEOUT 129 
#define  PLIP_SET_TIMEOUT 128 
 int SIOCDEVPLIP ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct net_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
plip_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct net_local *nl = netdev_priv(dev);
	struct plipconf *pc = (struct plipconf *) &rq->ifr_ifru;

	if (cmd != SIOCDEVPLIP)
		return -EOPNOTSUPP;

	switch(pc->pcmd) {
	case PLIP_GET_TIMEOUT:
		pc->trigger = nl->trigger;
		pc->nibble  = nl->nibble;
		break;
	case PLIP_SET_TIMEOUT:
		if(!capable(CAP_NET_ADMIN))
			return -EPERM;
		nl->trigger = pc->trigger;
		nl->nibble  = pc->nibble;
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}