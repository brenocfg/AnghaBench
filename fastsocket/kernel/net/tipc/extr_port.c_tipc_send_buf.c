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
struct TYPE_2__ {int congested; struct tipc_msg phdr; int /*<<< orphan*/  connected; } ;
struct port {TYPE_1__ publ; int /*<<< orphan*/  sent; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ELINKCONG ; 
 int ENOMEM ; 
 scalar_t__ likely (int) ; 
 scalar_t__ msg_destnode (struct tipc_msg*) ; 
 scalar_t__ msg_hdr_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  port_incr_out_seqno (struct port*) ; 
 scalar_t__ port_unreliable (struct port*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,scalar_t__) ; 
 scalar_t__ skb_cow (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 scalar_t__ tipc_own_addr ; 
 int /*<<< orphan*/  tipc_port_congested (struct port*) ; 
 struct port* tipc_port_deref (scalar_t__) ; 
 int /*<<< orphan*/  tipc_port_recv_msg (struct sk_buff*) ; 
 scalar_t__ tipc_send_buf_fast (struct sk_buff*,scalar_t__) ; 

int tipc_send_buf(u32 ref, struct sk_buff *buf, unsigned int dsz)
{
	struct port *p_ptr;
	struct tipc_msg *msg;
	u32 destnode;
	u32 hsz;
	u32 sz;
	u32 res;

	p_ptr = tipc_port_deref(ref);
	if (!p_ptr || !p_ptr->publ.connected)
		return -EINVAL;

	msg = &p_ptr->publ.phdr;
	hsz = msg_hdr_sz(msg);
	sz = hsz + dsz;
	msg_set_size(msg, sz);
	if (skb_cow(buf, hsz))
		return -ENOMEM;

	skb_push(buf, hsz);
	skb_copy_to_linear_data(buf, msg, hsz);
	destnode = msg_destnode(msg);
	p_ptr->publ.congested = 1;
	if (!tipc_port_congested(p_ptr)) {
		if (likely(destnode != tipc_own_addr))
			res = tipc_send_buf_fast(buf, destnode);
		else {
			tipc_port_recv_msg(buf);
			res = sz;
		}
		if (likely(res != -ELINKCONG)) {
			port_incr_out_seqno(p_ptr);
			p_ptr->sent++;
			p_ptr->publ.congested = 0;
			return res;
		}
	}
	if (port_unreliable(p_ptr)) {
		p_ptr->publ.congested = 0;
		return dsz;
	}
	return -ELINKCONG;
}