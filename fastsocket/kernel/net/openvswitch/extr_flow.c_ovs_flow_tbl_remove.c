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
struct sw_flow {int /*<<< orphan*/ * hash_node; } ;
struct flow_table {scalar_t__ count; size_t node_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 

void ovs_flow_tbl_remove(struct flow_table *table, struct sw_flow *flow)
{
	BUG_ON(table->count == 0);
	hlist_del_rcu(&flow->hash_node[table->node_ver]);
	table->count--;
}