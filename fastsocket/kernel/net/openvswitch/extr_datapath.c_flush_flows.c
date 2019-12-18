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
struct flow_table {int dummy; } ;
struct datapath {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TBL_MIN_BUCKETS ; 
 struct flow_table* ovs_flow_tbl_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_flow_tbl_deferred_destroy (struct flow_table*) ; 
 struct flow_table* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct flow_table*) ; 

__attribute__((used)) static int flush_flows(struct datapath *dp)
{
	struct flow_table *old_table;
	struct flow_table *new_table;

	old_table = ovsl_dereference(dp->table);
	new_table = ovs_flow_tbl_alloc(TBL_MIN_BUCKETS);
	if (!new_table)
		return -ENOMEM;

	rcu_assign_pointer(dp->table, new_table);

	ovs_flow_tbl_deferred_destroy(old_table);
	return 0;
}