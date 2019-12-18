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
struct netfs_trans_dst {int /*<<< orphan*/  trans_entry; struct netfs_trans* trans; } ;
struct netfs_trans {int /*<<< orphan*/  dst_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netfs_trans_remove_dst (struct netfs_trans_dst*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void netfs_trans_drop_dst(struct netfs_trans_dst *dst)
{
	struct netfs_trans *t = dst->trans;

	spin_lock(&t->dst_lock);
	list_del_init(&dst->trans_entry);
	spin_unlock(&t->dst_lock);

	netfs_trans_remove_dst(dst);
}