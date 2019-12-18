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
typedef  int u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cluster {int highest_node; int addr; scalar_t__* nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_ROUTING_TABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int in_own_cluster (int) ; 
 int /*<<< orphan*/  is_slave (int) ; 
 int /*<<< orphan*/  msg_set_dataoctet (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_remote_node (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_cltr_prepare_routing_msg (int,int) ; 
 int /*<<< orphan*/  tipc_link_send (struct sk_buff*,int,int) ; 
 scalar_t__ tipc_node_has_active_links (scalar_t__) ; 
 int /*<<< orphan*/  warn (char*) ; 

void tipc_cltr_send_ext_routes(struct cluster *c_ptr, u32 dest)
{
	struct sk_buff *buf;
	struct tipc_msg *msg;
	u32 highest = c_ptr->highest_node;
	u32 n_num;
	int send = 0;

	if (in_own_cluster(c_ptr->addr))
		return;
	assert(!is_slave(dest));
	assert(in_own_cluster(dest));
	highest = c_ptr->highest_node;
	buf = tipc_cltr_prepare_routing_msg(highest + 1, c_ptr->addr);
	if (buf) {
		msg = buf_msg(buf);
		msg_set_remote_node(msg, c_ptr->addr);
		msg_set_type(msg, EXT_ROUTING_TABLE);
		for (n_num = 1; n_num <= highest; n_num++) {
			if (c_ptr->nodes[n_num] &&
			    tipc_node_has_active_links(c_ptr->nodes[n_num])) {
				send = 1;
				msg_set_dataoctet(msg, n_num);
			}
		}
		if (send)
			tipc_link_send(buf, dest, dest);
		else
			buf_discard(buf);
	} else {
		warn("Memory squeeze: broadcast of external route failed\n");
	}
}