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
struct net_bridge_mdb_htable {size_t ver; int /*<<< orphan*/  size; } ;
struct net_bridge_mdb_entry {int mglist; int /*<<< orphan*/  rcu; int /*<<< orphan*/  query_timer; int /*<<< orphan*/ * hlist; scalar_t__ ports; int /*<<< orphan*/  timer; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; struct net_bridge_mdb_htable* mdb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_multicast_free_group ; 
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_group_expired(unsigned long data)
{
	struct net_bridge_mdb_entry *mp = (void *)data;
	struct net_bridge *br = mp->br;
	struct net_bridge_mdb_htable *mdb;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev) || timer_pending(&mp->timer))
		goto out;

	mp->mglist = false;

	if (mp->ports)
		goto out;

	mdb = br->mdb;
	hlist_del_rcu(&mp->hlist[mdb->ver]);
	mdb->size--;

	del_timer(&mp->query_timer);
	call_rcu_bh(&mp->rcu, br_multicast_free_group);

out:
	spin_unlock(&br->multicast_lock);
}