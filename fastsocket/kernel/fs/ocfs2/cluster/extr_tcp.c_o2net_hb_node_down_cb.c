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
struct o2nm_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2net_connected_peers ; 
 int /*<<< orphan*/  o2net_disconnect_node (struct o2nm_node*) ; 
 int o2nm_this_node () ; 
 int /*<<< orphan*/  o2quo_hb_down (int) ; 

__attribute__((used)) static void o2net_hb_node_down_cb(struct o2nm_node *node, int node_num,
				  void *data)
{
	o2quo_hb_down(node_num);

	if (node_num != o2nm_this_node())
		o2net_disconnect_node(node);

	BUG_ON(atomic_read(&o2net_connected_peers) < 0);
}