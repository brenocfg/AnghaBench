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
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ published; scalar_t__ congested; scalar_t__ connected; } ;
struct port {scalar_t__ last_in_seqno; int /*<<< orphan*/  probing_state; TYPE_1__ publ; int /*<<< orphan*/  (* wakeup ) (TYPE_1__*) ;int /*<<< orphan*/  acked; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIRMED ; 
 scalar_t__ CONN_ACK ; 
 int /*<<< orphan*/  CONN_MANAGER ; 
 scalar_t__ CONN_PROBE ; 
 int /*<<< orphan*/  CONN_PROBE_REPLY ; 
 int /*<<< orphan*/  TIPC_CONN_MSG ; 
 scalar_t__ TIPC_ERR_NO_PORT ; 
 int /*<<< orphan*/  TIPC_HIGH_IMPORTANCE ; 
 scalar_t__ TIPC_OK ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 int /*<<< orphan*/  msg_destport (struct tipc_msg*) ; 
 scalar_t__ msg_msgcnt (struct tipc_msg*) ; 
 scalar_t__ msg_orignode (struct tipc_msg*) ; 
 scalar_t__ msg_origport (struct tipc_msg*) ; 
 scalar_t__ msg_routed (struct tipc_msg*) ; 
 scalar_t__ msg_transp_seqno (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 struct sk_buff* port_build_proto_msg (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* port_build_self_abort_msg (struct port*,scalar_t__) ; 
 int /*<<< orphan*/  port_incr_out_seqno (struct port*) ; 
 int /*<<< orphan*/  port_out_seqno (struct port*) ; 
 scalar_t__ port_peernode (struct port*) ; 
 scalar_t__ port_peerport (struct port*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 scalar_t__ tipc_port_congested (struct port*) ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

void tipc_port_recv_proto_msg(struct sk_buff *buf)
{
	struct tipc_msg *msg = buf_msg(buf);
	struct port *p_ptr = tipc_port_lock(msg_destport(msg));
	u32 err = TIPC_OK;
	struct sk_buff *r_buf = NULL;
	struct sk_buff *abort_buf = NULL;

	msg_dbg(msg, "PORT<RECV<:");

	if (!p_ptr) {
		err = TIPC_ERR_NO_PORT;
	} else if (p_ptr->publ.connected) {
		if (port_peernode(p_ptr) != msg_orignode(msg))
			err = TIPC_ERR_NO_PORT;
		if (port_peerport(p_ptr) != msg_origport(msg))
			err = TIPC_ERR_NO_PORT;
		if (!err && msg_routed(msg)) {
			u32 seqno = msg_transp_seqno(msg);
			u32 myno =  ++p_ptr->last_in_seqno;
			if (seqno != myno) {
				err = TIPC_ERR_NO_PORT;
				abort_buf = port_build_self_abort_msg(p_ptr, err);
			}
		}
		if (msg_type(msg) == CONN_ACK) {
			int wakeup = tipc_port_congested(p_ptr) &&
				     p_ptr->publ.congested &&
				     p_ptr->wakeup;
			p_ptr->acked += msg_msgcnt(msg);
			if (tipc_port_congested(p_ptr))
				goto exit;
			p_ptr->publ.congested = 0;
			if (!wakeup)
				goto exit;
			p_ptr->wakeup(&p_ptr->publ);
			goto exit;
		}
	} else if (p_ptr->publ.published) {
		err = TIPC_ERR_NO_PORT;
	}
	if (err) {
		r_buf = port_build_proto_msg(msg_origport(msg),
					     msg_orignode(msg),
					     msg_destport(msg),
					     tipc_own_addr,
					     TIPC_HIGH_IMPORTANCE,
					     TIPC_CONN_MSG,
					     err,
					     0,
					     0);
		goto exit;
	}

	/* All is fine */
	if (msg_type(msg) == CONN_PROBE) {
		r_buf = port_build_proto_msg(msg_origport(msg),
					     msg_orignode(msg),
					     msg_destport(msg),
					     tipc_own_addr,
					     CONN_MANAGER,
					     CONN_PROBE_REPLY,
					     TIPC_OK,
					     port_out_seqno(p_ptr),
					     0);
	}
	p_ptr->probing_state = CONFIRMED;
	port_incr_out_seqno(p_ptr);
exit:
	if (p_ptr)
		tipc_port_unlock(p_ptr);
	tipc_net_route_msg(r_buf);
	tipc_net_route_msg(abort_buf);
	buf_discard(buf);
}