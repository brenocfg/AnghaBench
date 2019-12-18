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
struct net_bridge_port_group {int /*<<< orphan*/  rcu; int /*<<< orphan*/  query_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  mglist; struct net_bridge_port_group* next; int /*<<< orphan*/  addr; } ;
struct net_bridge_mdb_htable {int dummy; } ;
struct net_bridge_mdb_entry {int /*<<< orphan*/  timer; scalar_t__ timer_armed; int /*<<< orphan*/  mglist; struct net_bridge_port_group* ports; } ;
struct net_bridge {int /*<<< orphan*/  dev; struct net_bridge_mdb_htable* mdb; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct net_bridge_mdb_entry* br_mdb_ip_get (struct net_bridge_mdb_htable*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_multicast_free_pg ; 
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void br_multicast_del_pg(struct net_bridge *br,
				struct net_bridge_port_group *pg)
{
	struct net_bridge_mdb_htable *mdb = br->mdb;
	struct net_bridge_mdb_entry *mp;
	struct net_bridge_port_group *p;
	struct net_bridge_port_group **pp;

	mp = br_mdb_ip_get(mdb, &pg->addr);
	if (WARN_ON(!mp))
		return;

	for (pp = &mp->ports; (p = *pp); pp = &p->next) {
		if (p != pg)
			continue;

		*pp = p->next;
		hlist_del_init(&p->mglist);
		del_timer(&p->timer);
		del_timer(&p->query_timer);
		call_rcu_bh(&p->rcu, br_multicast_free_pg);

		if (!mp->ports && !mp->mglist && mp->timer_armed &&
		    netif_running(br->dev))
			mod_timer(&mp->timer, jiffies);

		return;
	}

	WARN_ON(1);
}