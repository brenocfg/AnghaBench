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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LONG_H_SIZE ; 
 struct sk_buff* buf_acquire (int /*<<< orphan*/ ) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 int /*<<< orphan*/  msg_init (struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_errcode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_msgcnt (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_orignode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_transp_seqno (struct tipc_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *port_build_proto_msg(u32 destport, u32 destnode,
					    u32 origport, u32 orignode,
					    u32 usr, u32 type, u32 err,
					    u32 seqno, u32 ack)
{
	struct sk_buff *buf;
	struct tipc_msg *msg;

	buf = buf_acquire(LONG_H_SIZE);
	if (buf) {
		msg = buf_msg(buf);
		msg_init(msg, usr, type, LONG_H_SIZE, destnode);
		msg_set_errcode(msg, err);
		msg_set_destport(msg, destport);
		msg_set_origport(msg, origport);
		msg_set_orignode(msg, orignode);
		msg_set_transp_seqno(msg, seqno);
		msg_set_msgcnt(msg, ack);
		msg_dbg(msg, "PORT>SEND>:");
	}
	return buf;
}