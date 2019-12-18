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
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_ERR_NO_NAME ; 
 scalar_t__ addr_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 int /*<<< orphan*/  msg_lookup_scope (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_named (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nameinst (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nametype (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,scalar_t__) ; 
 scalar_t__ tipc_nametbl_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_reject_msg (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void net_route_named_msg(struct sk_buff *buf)
{
	struct tipc_msg *msg = buf_msg(buf);
	u32 dnode;
	u32 dport;

	if (!msg_named(msg)) {
		msg_dbg(msg, "tipc_net->drop_nam:");
		buf_discard(buf);
		return;
	}

	dnode = addr_domain(msg_lookup_scope(msg));
	dport = tipc_nametbl_translate(msg_nametype(msg), msg_nameinst(msg), &dnode);
	dbg("tipc_net->lookup<%u,%u>-><%u,%x>\n",
	    msg_nametype(msg), msg_nameinst(msg), dport, dnode);
	if (dport) {
		msg_set_destnode(msg, dnode);
		msg_set_destport(msg, dport);
		tipc_net_route_msg(buf);
		return;
	}
	msg_dbg(msg, "tipc_net->rej:NO NAME: ");
	tipc_reject_msg(buf, TIPC_ERR_NO_NAME);
}