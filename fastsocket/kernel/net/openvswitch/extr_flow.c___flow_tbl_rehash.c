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

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct flow_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_table_copy_flows (struct flow_table*,struct flow_table*) ; 
 struct flow_table* ovs_flow_tbl_alloc (int) ; 

__attribute__((used)) static struct flow_table *__flow_tbl_rehash(struct flow_table *table, int n_buckets)
{
	struct flow_table *new_table;

	new_table = ovs_flow_tbl_alloc(n_buckets);
	if (!new_table)
		return ERR_PTR(-ENOMEM);

	flow_table_copy_flows(table, new_table);

	return new_table;
}