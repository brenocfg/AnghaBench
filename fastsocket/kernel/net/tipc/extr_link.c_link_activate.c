#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int recv_info; } ;
struct link {int next_in_no; int /*<<< orphan*/  addr; int /*<<< orphan*/  b_ptr; int /*<<< orphan*/  owner; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_own_cluster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_send_event (int /*<<< orphan*/ ,struct link*,int) ; 
 int /*<<< orphan*/  tipc_bearer_add_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cfg_link_event ; 
 int /*<<< orphan*/  tipc_disc_link_event ; 
 int /*<<< orphan*/  tipc_node_link_up (int /*<<< orphan*/ ,struct link*) ; 

__attribute__((used)) static void link_activate(struct link *l_ptr)
{
	l_ptr->next_in_no = l_ptr->stats.recv_info = 1;
	tipc_node_link_up(l_ptr->owner, l_ptr);
	tipc_bearer_add_dest(l_ptr->b_ptr, l_ptr->addr);
	link_send_event(tipc_cfg_link_event, l_ptr, 1);
	if (!in_own_cluster(l_ptr->addr))
		link_send_event(tipc_disc_link_event, l_ptr, 1);
}