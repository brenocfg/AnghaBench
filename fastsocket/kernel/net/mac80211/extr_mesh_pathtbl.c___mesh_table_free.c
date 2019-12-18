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
struct mesh_table {struct mesh_table* hashwlock; struct mesh_table* hash_buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mesh_table*) ; 

__attribute__((used)) static void __mesh_table_free(struct mesh_table *tbl)
{
	kfree(tbl->hash_buckets);
	kfree(tbl->hashwlock);
	kfree(tbl);
}