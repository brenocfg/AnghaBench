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
struct TYPE_2__ {struct link* buf; } ;
struct link {int /*<<< orphan*/  timer; int /*<<< orphan*/  owner; TYPE_1__ print_buf; int /*<<< orphan*/  link_list; } ;

/* Variables and functions */
 scalar_t__ LINK_LOG_BUF_SIZE ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  k_cancel_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k_term_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct link*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_link_reset (struct link*) ; 
 int /*<<< orphan*/  tipc_link_stop (struct link*) ; 
 int /*<<< orphan*/  tipc_node_detach_link (int /*<<< orphan*/ ,struct link*) ; 
 int /*<<< orphan*/  tipc_node_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_unlock (int /*<<< orphan*/ ) ; 

void tipc_link_delete(struct link *l_ptr)
{
	if (!l_ptr) {
		err("Attempt to delete non-existent link\n");
		return;
	}

	dbg("tipc_link_delete()\n");

	k_cancel_timer(&l_ptr->timer);

	tipc_node_lock(l_ptr->owner);
	tipc_link_reset(l_ptr);
	tipc_node_detach_link(l_ptr->owner, l_ptr);
	tipc_link_stop(l_ptr);
	list_del_init(&l_ptr->link_list);
	if (LINK_LOG_BUF_SIZE)
		kfree(l_ptr->print_buf.buf);
	tipc_node_unlock(l_ptr->owner);
	k_term_timer(&l_ptr->timer);
	kfree(l_ptr);
}