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
struct cluster {scalar_t__ highest_slave; scalar_t__ addr; scalar_t__* nodes; } ;

/* Variables and functions */
 scalar_t__ LOWEST_SLAVE ; 
 int /*<<< orphan*/  SLAVE_ROUTING_TABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int in_own_cluster (scalar_t__) ; 
 int /*<<< orphan*/  is_slave (scalar_t__) ; 
 int /*<<< orphan*/  msg_set_dataoctet (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_remote_node (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_cltr_prepare_routing_msg (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tipc_link_send (struct sk_buff*,scalar_t__,scalar_t__) ; 
 scalar_t__ tipc_node_has_active_links (scalar_t__) ; 
 int /*<<< orphan*/  warn (char*) ; 

void tipc_cltr_send_slave_routes(struct cluster *c_ptr, u32 dest)
{
	struct sk_buff *buf;
	struct tipc_msg *msg;
	u32 highest = c_ptr->highest_slave;
	u32 n_num;
	int send = 0;

	assert(!is_slave(dest));
	assert(in_own_cluster(dest));
	assert(in_own_cluster(c_ptr->addr));
	if (highest <= LOWEST_SLAVE)
		return;
	buf = tipc_cltr_prepare_routing_msg(highest - LOWEST_SLAVE + 1,
					    c_ptr->addr);
	if (buf) {
		msg = buf_msg(buf);
		msg_set_remote_node(msg, c_ptr->addr);
		msg_set_type(msg, SLAVE_ROUTING_TABLE);
		for (n_num = LOWEST_SLAVE; n_num <= highest; n_num++) {
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
		warn("Memory squeeze: broadcast of lost route failed\n");
	}
}