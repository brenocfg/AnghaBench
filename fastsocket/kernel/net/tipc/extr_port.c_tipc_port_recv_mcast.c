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
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct port_list {int count; int /*<<< orphan*/ * ports; struct port_list* next; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PLSIZE ; 
 int /*<<< orphan*/  TIPC_CLUSTER_SCOPE ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 int /*<<< orphan*/  msg_namelower (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nametype (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nameupper (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nametbl_mc_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct port_list*) ; 
 int /*<<< orphan*/  tipc_port_list_free (struct port_list*) ; 
 int /*<<< orphan*/  tipc_port_recv_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  warn (char*) ; 

void tipc_port_recv_mcast(struct sk_buff *buf, struct port_list *dp)
{
	struct tipc_msg* msg;
	struct port_list dports = {0, NULL, };
	struct port_list *item = dp;
	int cnt = 0;

	msg = buf_msg(buf);

	/* Create destination port list, if one wasn't supplied */

	if (dp == NULL) {
		tipc_nametbl_mc_translate(msg_nametype(msg),
				     msg_namelower(msg),
				     msg_nameupper(msg),
				     TIPC_CLUSTER_SCOPE,
				     &dports);
		item = dp = &dports;
	}

	/* Deliver a copy of message to each destination port */

	if (dp->count != 0) {
		if (dp->count == 1) {
			msg_set_destport(msg, dp->ports[0]);
			tipc_port_recv_msg(buf);
			tipc_port_list_free(dp);
			return;
		}
		for (; cnt < dp->count; cnt++) {
			int index = cnt % PLSIZE;
			struct sk_buff *b = skb_clone(buf, GFP_ATOMIC);

			if (b == NULL) {
				warn("Unable to deliver multicast message(s)\n");
				msg_dbg(msg, "LOST:");
				goto exit;
			}
			if ((index == 0) && (cnt != 0)) {
				item = item->next;
			}
			msg_set_destport(buf_msg(b),item->ports[index]);
			tipc_port_recv_msg(b);
		}
	}
exit:
	buf_discard(buf);
	tipc_port_list_free(dp);
}