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
typedef  size_t u32 ;
struct tipc_node {struct link** links; struct link** active_links; } ;
struct link {size_t priority; } ;

/* Variables and functions */
 size_t MAX_BEARERS ; 
 int /*<<< orphan*/  tipc_link_is_up (struct link*) ; 

__attribute__((used)) static void node_select_active_links(struct tipc_node *n_ptr)
{
	struct link **active = &n_ptr->active_links[0];
	u32 i;
	u32 highest_prio = 0;

	active[0] = active[1] = NULL;

	for (i = 0; i < MAX_BEARERS; i++) {
		struct link *l_ptr = n_ptr->links[i];

		if (!l_ptr || !tipc_link_is_up(l_ptr) ||
		    (l_ptr->priority < highest_prio))
			continue;

		if (l_ptr->priority > highest_prio) {
			highest_prio = l_ptr->priority;
			active[0] = active[1] = l_ptr;
		} else {
			active[1] = l_ptr;
		}
	}
}