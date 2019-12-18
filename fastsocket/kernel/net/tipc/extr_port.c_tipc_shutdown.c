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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phdr; scalar_t__ connected; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TIPC_CONN_MSG ; 
 int /*<<< orphan*/  TIPC_CONN_SHUTDOWN ; 
 scalar_t__ TIPC_CRITICAL_IMPORTANCE ; 
 scalar_t__ msg_importance (int /*<<< orphan*/ *) ; 
 struct sk_buff* port_build_proto_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_out_seqno (struct port*) ; 
 int /*<<< orphan*/  port_peernode (struct port*) ; 
 int /*<<< orphan*/  port_peerport (struct port*) ; 
 int tipc_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 struct port* tipc_port_lock (scalar_t__) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

int tipc_shutdown(u32 ref)
{
	struct port *p_ptr;
	struct sk_buff *buf = NULL;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return -EINVAL;

	if (p_ptr->publ.connected) {
		u32 imp = msg_importance(&p_ptr->publ.phdr);
		if (imp < TIPC_CRITICAL_IMPORTANCE)
			imp++;
		buf = port_build_proto_msg(port_peerport(p_ptr),
					   port_peernode(p_ptr),
					   ref,
					   tipc_own_addr,
					   imp,
					   TIPC_CONN_MSG,
					   TIPC_CONN_SHUTDOWN,
					   port_out_seqno(p_ptr),
					   0);
	}
	tipc_port_unlock(p_ptr);
	tipc_net_route_msg(buf);
	return tipc_disconnect(ref);
}