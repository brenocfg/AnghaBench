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
struct sw_flow_key {int dummy; } ;
struct sw_flow {int /*<<< orphan*/  key; int /*<<< orphan*/  hash; } ;
struct flow_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flow_tbl_insert (struct flow_table*,struct sw_flow*) ; 
 int /*<<< orphan*/  flow_key_start (struct sw_flow_key*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sw_flow_key*,int) ; 
 int /*<<< orphan*/  ovs_flow_hash (struct sw_flow_key*,int /*<<< orphan*/ ,int) ; 

void ovs_flow_tbl_insert(struct flow_table *table, struct sw_flow *flow,
			 struct sw_flow_key *key, int key_len)
{
	flow->hash = ovs_flow_hash(key, flow_key_start(key), key_len);
	memcpy(&flow->key, key, sizeof(flow->key));
	__flow_tbl_insert(table, flow);
}