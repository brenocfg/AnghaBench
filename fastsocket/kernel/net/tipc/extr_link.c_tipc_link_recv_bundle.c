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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_H_SIZE ; 
 scalar_t__ align (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct sk_buff* buf_extract (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_msgcnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_net_route_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  warn (char*) ; 

void tipc_link_recv_bundle(struct sk_buff *buf)
{
	u32 msgcount = msg_msgcnt(buf_msg(buf));
	u32 pos = INT_H_SIZE;
	struct sk_buff *obuf;

	msg_dbg(buf_msg(buf), "<BNDL<: ");
	while (msgcount--) {
		obuf = buf_extract(buf, pos);
		if (obuf == NULL) {
			warn("Link unable to unbundle message(s)\n");
			break;
		}
		pos += align(msg_size(buf_msg(obuf)));
		msg_dbg(buf_msg(obuf), "     /");
		tipc_net_route_msg(obuf);
	}
	buf_discard(buf);
}