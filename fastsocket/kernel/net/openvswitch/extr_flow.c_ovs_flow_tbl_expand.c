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
struct flow_table {int n_buckets; } ;

/* Variables and functions */
 struct flow_table* __flow_tbl_rehash (struct flow_table*,int) ; 

struct flow_table *ovs_flow_tbl_expand(struct flow_table *table)
{
	return __flow_tbl_rehash(table, table->n_buckets * 2);
}