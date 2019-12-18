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
struct net_device {struct dn_dev* dn_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* down ) (struct net_device*) ;} ;
struct dn_dev {scalar_t__ peer; scalar_t__ router; int /*<<< orphan*/  neigh_parms; TYPE_1__ parms; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dn_dev_check_default (struct net_device*) ; 
 int /*<<< orphan*/  dn_dev_sysctl_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  dn_neigh_table ; 
 int /*<<< orphan*/  kfree (struct dn_dev*) ; 
 int /*<<< orphan*/  neigh_ifdown (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_parms_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_release (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static void dn_dev_delete(struct net_device *dev)
{
	struct dn_dev *dn_db = dev->dn_ptr;

	if (dn_db == NULL)
		return;

	del_timer_sync(&dn_db->timer);
	dn_dev_sysctl_unregister(&dn_db->parms);
	dn_dev_check_default(dev);
	neigh_ifdown(&dn_neigh_table, dev);

	if (dn_db->parms.down)
		dn_db->parms.down(dev);

	dev->dn_ptr = NULL;

	neigh_parms_release(&dn_neigh_table, dn_db->neigh_parms);
	neigh_ifdown(&dn_neigh_table, dev);

	if (dn_db->router)
		neigh_release(dn_db->router);
	if (dn_db->peer)
		neigh_release(dn_db->peer);

	kfree(dn_db);
}