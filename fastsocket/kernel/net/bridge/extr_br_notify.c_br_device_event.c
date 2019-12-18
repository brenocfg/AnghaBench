#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; struct net_bridge_port* br_port; } ;
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  lock; TYPE_1__* dev; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
#define  NETDEV_CHANGE 134 
#define  NETDEV_CHANGEADDR 133 
#define  NETDEV_CHANGEMTU 132 
#define  NETDEV_DOWN 131 
#define  NETDEV_FEAT_CHANGE 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  br_del_if (struct net_bridge*,struct net_device*) ; 
 int /*<<< orphan*/  br_fdb_changeaddr (struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_features_recompute (struct net_bridge*) ; 
 int /*<<< orphan*/  br_ifinfo_notify (int /*<<< orphan*/ ,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_min_mtu (struct net_bridge*) ; 
 int /*<<< orphan*/  br_port_carrier_check (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_stp_disable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_stp_enable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_stp_recalculate_bridge_id (struct net_bridge*) ; 
 int /*<<< orphan*/  dev_set_mtu (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int br_device_event(struct notifier_block *unused, unsigned long event, void *ptr)
{
	struct net_device *dev = ptr;
	struct net_bridge_port *p = dev->br_port;
	struct net_bridge *br;

	/* not a port of a bridge */
	if (p == NULL)
		return NOTIFY_DONE;

	br = p->br;

	switch (event) {
	case NETDEV_CHANGEMTU:
		dev_set_mtu(br->dev, br_min_mtu(br));
		break;

	case NETDEV_CHANGEADDR:
		spin_lock_bh(&br->lock);
		br_fdb_changeaddr(p, dev->dev_addr);
		br_stp_recalculate_bridge_id(br);
		spin_unlock_bh(&br->lock);
		break;

	case NETDEV_CHANGE:
		br_port_carrier_check(p);
		break;

	case NETDEV_FEAT_CHANGE:
		if (netif_running(br->dev))
			br_features_recompute(br);
		break;

	case NETDEV_DOWN:
		spin_lock_bh(&br->lock);
		if (br->dev->flags & IFF_UP)
			br_stp_disable_port(p);
		spin_unlock_bh(&br->lock);
		break;

	case NETDEV_UP:
		if (netif_carrier_ok(dev) && (br->dev->flags & IFF_UP)) {
			spin_lock_bh(&br->lock);
			br_stp_enable_port(p);
			spin_unlock_bh(&br->lock);
		}
		break;

	case NETDEV_UNREGISTER:
		br_del_if(br, dev);
		break;
	}

	/* Events that may cause spanning tree to refresh */
	if (event == NETDEV_CHANGEADDR || event == NETDEV_UP ||
	    event == NETDEV_CHANGE || event == NETDEV_DOWN)
		br_ifinfo_notify(RTM_NEWLINK, p);

	return NOTIFY_DONE;
}