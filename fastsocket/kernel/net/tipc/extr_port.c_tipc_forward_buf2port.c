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
struct tipc_portid {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {struct tipc_msg phdr; scalar_t__ connected; } ;
struct port {int /*<<< orphan*/  sent; TYPE_1__ publ; } ;

/* Variables and functions */
 scalar_t__ DIR_MSG_H_SIZE ; 
 int EINVAL ; 
 int ELINKCONG ; 
 int ENOMEM ; 
 unsigned int TIPC_CRITICAL_IMPORTANCE ; 
 int /*<<< orphan*/  TIPC_DIRECT_MSG ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_hdr_sz (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_importance (struct tipc_msg*,unsigned int) ; 
 int /*<<< orphan*/  msg_set_orignode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 scalar_t__ port_unreliable (struct port*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,scalar_t__) ; 
 scalar_t__ skb_cow (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 int tipc_port_recv_msg (struct sk_buff*) ; 
 scalar_t__ tipc_ref_deref (int /*<<< orphan*/ ) ; 
 int tipc_send_buf_fast (struct sk_buff*,int /*<<< orphan*/ ) ; 

int tipc_forward_buf2port(u32 ref,
			  struct tipc_portid const *dest,
			  struct sk_buff *buf,
			  unsigned int dsz,
			  struct tipc_portid const *orig,
			  unsigned int importance)
{
	struct port *p_ptr;
	struct tipc_msg *msg;
	int res;

	p_ptr = (struct port *)tipc_ref_deref(ref);
	if (!p_ptr || p_ptr->publ.connected)
		return -EINVAL;

	msg = &p_ptr->publ.phdr;
	msg_set_type(msg, TIPC_DIRECT_MSG);
	msg_set_orignode(msg, orig->node);
	msg_set_origport(msg, orig->ref);
	msg_set_destnode(msg, dest->node);
	msg_set_destport(msg, dest->ref);
	msg_set_hdr_sz(msg, DIR_MSG_H_SIZE);
	if (importance <= TIPC_CRITICAL_IMPORTANCE)
		msg_set_importance(msg, importance);
	msg_set_size(msg, DIR_MSG_H_SIZE + dsz);
	if (skb_cow(buf, DIR_MSG_H_SIZE))
		return -ENOMEM;

	skb_push(buf, DIR_MSG_H_SIZE);
	skb_copy_to_linear_data(buf, msg, DIR_MSG_H_SIZE);
	msg_dbg(msg, "buf2port: ");
	p_ptr->sent++;
	if (dest->node == tipc_own_addr)
		return tipc_port_recv_msg(buf);
	res = tipc_send_buf_fast(buf, dest->node);
	if (likely(res != -ELINKCONG))
		return res;
	if (port_unreliable(p_ptr))
		return dsz;
	return -ELINKCONG;
}