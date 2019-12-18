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
struct sk_buff {int dummy; } ;
struct port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_ERR_NO_NODE ; 
 struct sk_buff* port_build_self_abort_msg (struct port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 struct port* tipc_port_lock (unsigned long) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

__attribute__((used)) static void port_handle_node_down(unsigned long ref)
{
	struct port *p_ptr = tipc_port_lock(ref);
	struct sk_buff* buf = NULL;

	if (!p_ptr)
		return;
	buf = port_build_self_abort_msg(p_ptr, TIPC_ERR_NO_NODE);
	tipc_port_unlock(p_ptr);
	tipc_net_route_msg(buf);
}