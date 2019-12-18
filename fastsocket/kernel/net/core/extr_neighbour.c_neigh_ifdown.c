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
struct net_device {int dummy; } ;
struct neigh_table {int /*<<< orphan*/  proxy_queue; int /*<<< orphan*/  proxy_timer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_flush_dev (struct neigh_table*,struct net_device*) ; 
 int /*<<< orphan*/  pneigh_ifdown (struct neigh_table*,struct net_device*) ; 
 int /*<<< orphan*/  pneigh_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int neigh_ifdown(struct neigh_table *tbl, struct net_device *dev)
{
	write_lock_bh(&tbl->lock);
	neigh_flush_dev(tbl, dev);
	pneigh_ifdown(tbl, dev);
	write_unlock_bh(&tbl->lock);

	del_timer_sync(&tbl->proxy_timer);
	pneigh_queue_purge(&tbl->proxy_queue);
	return 0;
}