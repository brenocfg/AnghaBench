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
struct TYPE_2__ {int /*<<< orphan*/  conn_unacked; scalar_t__ connected; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_ACK ; 
 int /*<<< orphan*/  CONN_MANAGER ; 
 int /*<<< orphan*/  TIPC_OK ; 
 struct sk_buff* port_build_proto_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_out_seqno (struct port*) ; 
 int /*<<< orphan*/  port_peernode (struct port*) ; 
 int /*<<< orphan*/  port_peerport (struct port*) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

void tipc_acknowledge(u32 ref, u32 ack)
{
	struct port *p_ptr;
	struct sk_buff *buf = NULL;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return;
	if (p_ptr->publ.connected) {
		p_ptr->publ.conn_unacked -= ack;
		buf = port_build_proto_msg(port_peerport(p_ptr),
					   port_peernode(p_ptr),
					   ref,
					   tipc_own_addr,
					   CONN_MANAGER,
					   CONN_ACK,
					   TIPC_OK,
					   port_out_seqno(p_ptr),
					   ack);
	}
	tipc_port_unlock(p_ptr);
	tipc_net_route_msg(buf);
}