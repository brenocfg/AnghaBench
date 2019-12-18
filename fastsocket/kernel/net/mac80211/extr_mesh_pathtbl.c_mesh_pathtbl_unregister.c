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

/* Variables and functions */
 int /*<<< orphan*/  mesh_paths ; 
 int /*<<< orphan*/  mesh_table_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpp_paths ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

void mesh_pathtbl_unregister(void)
{
	/* no need for locking during exit path */
	mesh_table_free(rcu_dereference_protected(mesh_paths, 1), true);
	mesh_table_free(rcu_dereference_protected(mpp_paths, 1), true);
}