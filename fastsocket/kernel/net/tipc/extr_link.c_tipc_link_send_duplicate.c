#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {struct sk_buff* next; int /*<<< orphan*/  data; } ;
struct link {TYPE_3__* b_ptr; TYPE_2__* owner; scalar_t__ next_in_no; struct sk_buff* first_out; int /*<<< orphan*/  peer_bearer_id; int /*<<< orphan*/  out_queue_size; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  net_plane; } ;
struct TYPE_4__ {int /*<<< orphan*/  last_in; } ;
struct TYPE_5__ {TYPE_1__ bclink; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGEOVER_PROTOCOL ; 
 int /*<<< orphan*/  CLOSED_MSG ; 
 int /*<<< orphan*/  DUPLICATE_MSG ; 
 scalar_t__ INT_H_SIZE ; 
 scalar_t__ MSG_BUNDLER ; 
 struct sk_buff* buf_acquire (scalar_t__) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod (scalar_t__) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 int /*<<< orphan*/  msg_init (struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_ack (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bcast_ack (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bearer_id (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_msgcnt (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 scalar_t__ msg_size (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tipc_link_is_up (struct link*) ; 
 int /*<<< orphan*/  tipc_link_send_buf (struct link*,struct sk_buff*) ; 
 int /*<<< orphan*/  warn (char*) ; 

void tipc_link_send_duplicate(struct link *l_ptr, struct link *tunnel)
{
	struct sk_buff *iter;
	struct tipc_msg tunnel_hdr;

	msg_init(&tunnel_hdr, CHANGEOVER_PROTOCOL,
		 DUPLICATE_MSG, INT_H_SIZE, l_ptr->addr);
	msg_set_msgcnt(&tunnel_hdr, l_ptr->out_queue_size);
	msg_set_bearer_id(&tunnel_hdr, l_ptr->peer_bearer_id);
	iter = l_ptr->first_out;
	while (iter) {
		struct sk_buff *outbuf;
		struct tipc_msg *msg = buf_msg(iter);
		u32 length = msg_size(msg);

		if (msg_user(msg) == MSG_BUNDLER)
			msg_set_type(msg, CLOSED_MSG);
		msg_set_ack(msg, mod(l_ptr->next_in_no - 1));	/* Update */
		msg_set_bcast_ack(msg, l_ptr->owner->bclink.last_in);
		msg_set_size(&tunnel_hdr, length + INT_H_SIZE);
		outbuf = buf_acquire(length + INT_H_SIZE);
		if (outbuf == NULL) {
			warn("Link changeover error, "
			     "unable to send duplicate msg\n");
			return;
		}
		skb_copy_to_linear_data(outbuf, &tunnel_hdr, INT_H_SIZE);
		skb_copy_to_linear_data_offset(outbuf, INT_H_SIZE, iter->data,
					       length);
		dbg("%c->%c:", l_ptr->b_ptr->net_plane,
		    tunnel->b_ptr->net_plane);
		msg_dbg(buf_msg(outbuf), ">SEND>");
		tipc_link_send_buf(tunnel, outbuf);
		if (!tipc_link_is_up(l_ptr))
			return;
		iter = iter->next;
	}
}