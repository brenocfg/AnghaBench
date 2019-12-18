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
struct TYPE_2__ {scalar_t__ connected; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 int LONG_H_SIZE ; 
 scalar_t__ MAX_REJECT_SIZE ; 
 int MCAST_H_SIZE ; 
 scalar_t__ TIPC_CRITICAL_IMPORTANCE ; 
 struct sk_buff* buf_acquire (scalar_t__) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 scalar_t__ msg_connected (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_data (struct tipc_msg*) ; 
 scalar_t__ msg_data_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 scalar_t__ msg_dest_droppable (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_destnode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_destport (struct tipc_msg*) ; 
 scalar_t__ msg_errcode (struct tipc_msg*) ; 
 scalar_t__ msg_importance (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_init (struct tipc_msg*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ msg_mcast (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nameinst (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nametype (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_origport (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_errcode (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_nameinst (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_nametype (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_orignode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 scalar_t__ msg_short (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_type (struct tipc_msg*) ; 
 struct sk_buff* port_build_self_abort_msg (struct port*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

int tipc_reject_msg(struct sk_buff *buf, u32 err)
{
	struct tipc_msg *msg = buf_msg(buf);
	struct sk_buff *rbuf;
	struct tipc_msg *rmsg;
	int hdr_sz;
	u32 imp = msg_importance(msg);
	u32 data_sz = msg_data_sz(msg);

	if (data_sz > MAX_REJECT_SIZE)
		data_sz = MAX_REJECT_SIZE;
	if (msg_connected(msg) && (imp < TIPC_CRITICAL_IMPORTANCE))
		imp++;
	msg_dbg(msg, "port->rej: ");

	/* discard rejected message if it shouldn't be returned to sender */
	if (msg_errcode(msg) || msg_dest_droppable(msg)) {
		buf_discard(buf);
		return data_sz;
	}

	/* construct rejected message */
	if (msg_mcast(msg))
		hdr_sz = MCAST_H_SIZE;
	else
		hdr_sz = LONG_H_SIZE;
	rbuf = buf_acquire(data_sz + hdr_sz);
	if (rbuf == NULL) {
		buf_discard(buf);
		return data_sz;
	}
	rmsg = buf_msg(rbuf);
	msg_init(rmsg, imp, msg_type(msg), hdr_sz, msg_orignode(msg));
	msg_set_errcode(rmsg, err);
	msg_set_destport(rmsg, msg_origport(msg));
	msg_set_origport(rmsg, msg_destport(msg));
	if (msg_short(msg)) {
		msg_set_orignode(rmsg, tipc_own_addr);
		/* leave name type & instance as zeroes */
	} else {
		msg_set_orignode(rmsg, msg_destnode(msg));
		msg_set_nametype(rmsg, msg_nametype(msg));
		msg_set_nameinst(rmsg, msg_nameinst(msg));
	}
	msg_set_size(rmsg, data_sz + hdr_sz);
	skb_copy_to_linear_data_offset(rbuf, hdr_sz, msg_data(msg), data_sz);

	/* send self-abort message when rejecting on a connected port */
	if (msg_connected(msg)) {
		struct sk_buff *abuf = NULL;
		struct port *p_ptr = tipc_port_lock(msg_destport(msg));

		if (p_ptr) {
			if (p_ptr->publ.connected)
				abuf = port_build_self_abort_msg(p_ptr, err);
			tipc_port_unlock(p_ptr);
		}
		tipc_net_route_msg(abuf);
	}

	/* send rejected message */
	buf_discard(buf);
	tipc_net_route_msg(rbuf);
	return data_sz;
}