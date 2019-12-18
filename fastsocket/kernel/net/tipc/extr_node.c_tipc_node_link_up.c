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
struct tipc_node {int /*<<< orphan*/  working_links; struct link** active_links; } ;
struct link {scalar_t__ priority; int /*<<< orphan*/  name; TYPE_1__* b_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  net_plane; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,struct link*,struct link**,struct link**) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  node_established_contact (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_link_send_duplicate (struct link*,struct link*) ; 

void tipc_node_link_up(struct tipc_node *n_ptr, struct link *l_ptr)
{
	struct link **active = &n_ptr->active_links[0];

	n_ptr->working_links++;

	info("Established link <%s> on network plane %c\n",
	     l_ptr->name, l_ptr->b_ptr->net_plane);

	if (!active[0]) {
		dbg(" link %x into %x/%x\n", l_ptr, &active[0], &active[1]);
		active[0] = active[1] = l_ptr;
		node_established_contact(n_ptr);
		return;
	}
	if (l_ptr->priority < active[0]->priority) {
		info("New link <%s> becomes standby\n", l_ptr->name);
		return;
	}
	tipc_link_send_duplicate(active[0], l_ptr);
	if (l_ptr->priority == active[0]->priority) {
		active[0] = l_ptr;
		return;
	}
	info("Old link <%s> becomes standby\n", active[0]->name);
	if (active[1] != active[0])
		info("Old link <%s> becomes standby\n", active[1]->name);
	active[0] = active[1] = l_ptr;
}