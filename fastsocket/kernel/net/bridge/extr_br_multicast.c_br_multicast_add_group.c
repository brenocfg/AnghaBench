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
struct br_ip {int dummy; } ;
struct net_bridge_port_group {int /*<<< orphan*/  query_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  mglist; struct net_bridge_port_group* next; struct net_bridge_port* port; struct br_ip addr; } ;
struct net_bridge_port {scalar_t__ state; int /*<<< orphan*/  mglist; } ;
struct net_bridge_mdb_entry {int mglist; struct net_bridge_port_group* ports; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; scalar_t__ multicast_membership_interval; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_DISABLED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct net_bridge_mdb_entry*) ; 
 int PTR_ERR (struct net_bridge_mdb_entry*) ; 
 struct net_bridge_mdb_entry* br_multicast_new_group (struct net_bridge*,struct net_bridge_port*,struct br_ip*) ; 
 int /*<<< orphan*/  br_multicast_port_group_expired ; 
 int /*<<< orphan*/  br_multicast_port_group_query_expired ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 struct net_bridge_port_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct net_bridge_port_group*,struct net_bridge_port_group*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int br_multicast_add_group(struct net_bridge *br,
				  struct net_bridge_port *port,
				  struct br_ip *group)
{
	struct net_bridge_mdb_entry *mp;
	struct net_bridge_port_group *p;
	struct net_bridge_port_group **pp;
	int err;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev) ||
	    (port && port->state == BR_STATE_DISABLED))
		goto out;

	mp = br_multicast_new_group(br, port, group);
	err = PTR_ERR(mp);
	if (unlikely(IS_ERR(mp) || !mp))
		goto err;

	if (!port) {
		mp->mglist = true;
		goto out;
	}

	for (pp = &mp->ports; (p = *pp); pp = &p->next) {
		if (p->port == port) {
			/* We already have a portgroup, update the timer.  */
			mod_timer(&p->timer,
				  jiffies + br->multicast_membership_interval);
			goto out;
		}
		if ((unsigned long)p->port < (unsigned long)port)
			break;
	}

	p = kzalloc(sizeof(*p), GFP_ATOMIC);
	err = -ENOMEM;
	if (unlikely(!p))
		goto err;

	p->addr = *group;
	p->port = port;
	p->next = *pp;
	hlist_add_head(&p->mglist, &port->mglist);
	setup_timer(&p->timer, br_multicast_port_group_expired,
		    (unsigned long)p);
	setup_timer(&p->query_timer, br_multicast_port_group_query_expired,
		    (unsigned long)p);

	rcu_assign_pointer(*pp, p);

out:
	err = 0;

err:
	spin_unlock(&br->multicast_lock);
	return err;
}