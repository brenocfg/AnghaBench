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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ connected; } ;
struct port {int /*<<< orphan*/  timer; int /*<<< orphan*/  wait_list; int /*<<< orphan*/  port_list; struct port* user_port; int /*<<< orphan*/  subscription; TYPE_1__ publ; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TIPC_ERR_NO_PORT ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_cancel_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k_term_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct port*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct sk_buff* port_build_peer_abort_msg (struct port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_nodesub_unsubscribe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_port_list_lock ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 
 int /*<<< orphan*/  tipc_ref_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_reg_remove_port (struct port*) ; 
 int /*<<< orphan*/  tipc_withdraw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int tipc_deleteport(u32 ref)
{
	struct port *p_ptr;
	struct sk_buff *buf = NULL;

	tipc_withdraw(ref, 0, NULL);
	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return -EINVAL;

	tipc_ref_discard(ref);
	tipc_port_unlock(p_ptr);

	k_cancel_timer(&p_ptr->timer);
	if (p_ptr->publ.connected) {
		buf = port_build_peer_abort_msg(p_ptr, TIPC_ERR_NO_PORT);
		tipc_nodesub_unsubscribe(&p_ptr->subscription);
	}
	if (p_ptr->user_port) {
		tipc_reg_remove_port(p_ptr->user_port);
		kfree(p_ptr->user_port);
	}

	spin_lock_bh(&tipc_port_list_lock);
	list_del(&p_ptr->port_list);
	list_del(&p_ptr->wait_list);
	spin_unlock_bh(&tipc_port_list_lock);
	k_term_timer(&p_ptr->timer);
	kfree(p_ptr);
	dbg("Deleted port %u\n", ref);
	tipc_net_route_msg(buf);
	return 0;
}