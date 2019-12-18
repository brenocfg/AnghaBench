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
struct mesh_table {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pathtbl_resize_lock ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct mesh_table* resize_dereference_mesh_paths () ; 
 struct mesh_table* resize_dereference_mpp_paths () ; 
 int /*<<< orphan*/  table_flush_by_iface (struct mesh_table*,struct ieee80211_sub_if_data*) ; 

void mesh_path_flush_by_iface(struct ieee80211_sub_if_data *sdata)
{
	struct mesh_table *tbl;

	rcu_read_lock();
	read_lock_bh(&pathtbl_resize_lock);
	tbl = resize_dereference_mesh_paths();
	table_flush_by_iface(tbl, sdata);
	tbl = resize_dereference_mpp_paths();
	table_flush_by_iface(tbl, sdata);
	read_unlock_bh(&pathtbl_resize_lock);
	rcu_read_unlock();
}