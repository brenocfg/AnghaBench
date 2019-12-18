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
struct tipc_node_subscr {int /*<<< orphan*/  node; int /*<<< orphan*/  nodesub_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_node_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_unlock (int /*<<< orphan*/ ) ; 

void tipc_nodesub_unsubscribe(struct tipc_node_subscr *node_sub)
{
	if (!node_sub->node)
		return;

	tipc_node_lock(node_sub->node);
	list_del_init(&node_sub->nodesub_list);
	tipc_node_unlock(node_sub->node);
}