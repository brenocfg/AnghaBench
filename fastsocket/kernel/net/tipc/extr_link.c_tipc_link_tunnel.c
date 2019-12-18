#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct link {TYPE_1__* b_ptr; TYPE_2__* owner; } ;
struct TYPE_4__ {struct link** active_links; } ;
struct TYPE_3__ {int /*<<< orphan*/  net_plane; } ;

/* Variables and functions */
 int INT_H_SIZE ; 
 struct sk_buff* buf_acquire (int) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,int) ; 
 int msg_size (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,struct tipc_msg*,int) ; 
 int /*<<< orphan*/  tipc_link_is_up (struct link*) ; 
 int /*<<< orphan*/  tipc_link_send_buf (struct link*,struct sk_buff*) ; 
 int /*<<< orphan*/  warn (char*) ; 

void tipc_link_tunnel(struct link *l_ptr,
		      struct tipc_msg *tunnel_hdr,
		      struct tipc_msg  *msg,
		      u32 selector)
{
	struct link *tunnel;
	struct sk_buff *buf;
	u32 length = msg_size(msg);

	tunnel = l_ptr->owner->active_links[selector & 1];
	if (!tipc_link_is_up(tunnel)) {
		warn("Link changeover error, "
		     "tunnel link no longer available\n");
		return;
	}
	msg_set_size(tunnel_hdr, length + INT_H_SIZE);
	buf = buf_acquire(length + INT_H_SIZE);
	if (!buf) {
		warn("Link changeover error, "
		     "unable to send tunnel msg\n");
		return;
	}
	skb_copy_to_linear_data(buf, tunnel_hdr, INT_H_SIZE);
	skb_copy_to_linear_data_offset(buf, INT_H_SIZE, msg, length);
	dbg("%c->%c:", l_ptr->b_ptr->net_plane, tunnel->b_ptr->net_plane);
	msg_dbg(buf_msg(buf), ">SEND>");
	tipc_link_send_buf(tunnel, buf);
}