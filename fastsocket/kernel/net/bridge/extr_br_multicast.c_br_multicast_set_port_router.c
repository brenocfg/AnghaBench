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
struct net_bridge_port {scalar_t__ state; unsigned long multicast_router; int /*<<< orphan*/  multicast_router_timer; int /*<<< orphan*/  rlist; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_DISABLED ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  br_multicast_add_router (struct net_bridge*,struct net_bridge_port*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int br_multicast_set_port_router(struct net_bridge_port *p, unsigned long val)
{
	struct net_bridge *br = p->br;
	int err = -ENOENT;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev) || p->state == BR_STATE_DISABLED)
		goto unlock;

	switch (val) {
	case 0:
	case 1:
	case 2:
		p->multicast_router = val;
		err = 0;

		if (val < 2 && !hlist_unhashed(&p->rlist))
			hlist_del_init_rcu(&p->rlist);

		if (val == 1)
			break;

		del_timer(&p->multicast_router_timer);

		if (val == 0)
			break;

		br_multicast_add_router(br, p);
		break;

	default:
		err = -EINVAL;
		break;
	}

unlock:
	spin_unlock(&br->multicast_lock);

	return err;
}