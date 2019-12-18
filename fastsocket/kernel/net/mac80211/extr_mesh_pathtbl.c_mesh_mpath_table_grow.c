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
struct mesh_table {int /*<<< orphan*/  rcu_head; scalar_t__ size_order; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mesh_table_free (struct mesh_table*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_paths ; 
 struct mesh_table* mesh_table_alloc (scalar_t__) ; 
 int /*<<< orphan*/  mesh_table_free_rcu ; 
 scalar_t__ mesh_table_grow (struct mesh_table*,struct mesh_table*) ; 
 int /*<<< orphan*/  pathtbl_resize_lock ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct mesh_table*) ; 
 struct mesh_table* resize_dereference_mesh_paths () ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void mesh_mpath_table_grow(void)
{
	struct mesh_table *oldtbl, *newtbl;

	write_lock_bh(&pathtbl_resize_lock);
	oldtbl = resize_dereference_mesh_paths();
	newtbl = mesh_table_alloc(oldtbl->size_order + 1);
	if (!newtbl)
		goto out;
	if (mesh_table_grow(oldtbl, newtbl) < 0) {
		__mesh_table_free(newtbl);
		goto out;
	}
	rcu_assign_pointer(mesh_paths, newtbl);

	call_rcu(&oldtbl->rcu_head, mesh_table_free_rcu);

 out:
	write_unlock_bh(&pathtbl_resize_lock);
}