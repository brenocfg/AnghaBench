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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  connected; } ;
struct port {scalar_t__ probing_state; int /*<<< orphan*/  probing_interval; int /*<<< orphan*/  timer; TYPE_1__ publ; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_MANAGER ; 
 int /*<<< orphan*/  CONN_PROBE ; 
 scalar_t__ PROBING ; 
 int /*<<< orphan*/  TIPC_ERR_NO_PORT ; 
 int /*<<< orphan*/  TIPC_OK ; 
 int /*<<< orphan*/  k_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* port_build_proto_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* port_build_self_abort_msg (struct port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_incr_out_seqno (struct port*) ; 
 int /*<<< orphan*/  port_out_seqno (struct port*) ; 
 int /*<<< orphan*/  port_peernode (struct port*) ; 
 int /*<<< orphan*/  port_peerport (struct port*) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 struct port* tipc_port_lock (unsigned long) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

__attribute__((used)) static void port_timeout(unsigned long ref)
{
	struct port *p_ptr = tipc_port_lock(ref);
	struct sk_buff *buf = NULL;

	if (!p_ptr)
		return;

	if (!p_ptr->publ.connected) {
		tipc_port_unlock(p_ptr);
		return;
	}

	/* Last probe answered ? */
	if (p_ptr->probing_state == PROBING) {
		buf = port_build_self_abort_msg(p_ptr, TIPC_ERR_NO_PORT);
	} else {
		buf = port_build_proto_msg(port_peerport(p_ptr),
					   port_peernode(p_ptr),
					   p_ptr->publ.ref,
					   tipc_own_addr,
					   CONN_MANAGER,
					   CONN_PROBE,
					   TIPC_OK,
					   port_out_seqno(p_ptr),
					   0);
		port_incr_out_seqno(p_ptr);
		p_ptr->probing_state = PROBING;
		k_start_timer(&p_ptr->timer, p_ptr->probing_interval);
	}
	tipc_port_unlock(p_ptr);
	tipc_net_route_msg(buf);
}