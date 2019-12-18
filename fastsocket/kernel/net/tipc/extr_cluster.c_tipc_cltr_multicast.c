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
struct tipc_node {int /*<<< orphan*/  addr; } ;
struct sk_buff {int dummy; } ;
struct cluster {int highest_slave; int highest_node; struct tipc_node** nodes; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LOWEST_SLAVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int in_own_cluster (int /*<<< orphan*/ ) ; 
 scalar_t__ is_slave (int) ; 
 int /*<<< orphan*/  msg_set_destnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int tipc_highest_allowed_slave ; 
 int /*<<< orphan*/  tipc_link_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tipc_max_nodes ; 
 scalar_t__ tipc_node_has_active_links (struct tipc_node*) ; 

__attribute__((used)) static void tipc_cltr_multicast(struct cluster *c_ptr, struct sk_buff *buf,
			 u32 lower, u32 upper)
{
	struct sk_buff *buf_copy;
	struct tipc_node *n_ptr;
	u32 n_num;
	u32 tstop;

	assert(lower <= upper);
	assert(((lower >= 1) && (lower <= tipc_max_nodes)) ||
	       ((lower >= LOWEST_SLAVE) && (lower <= tipc_highest_allowed_slave)));
	assert(((upper >= 1) && (upper <= tipc_max_nodes)) ||
	       ((upper >= LOWEST_SLAVE) && (upper <= tipc_highest_allowed_slave)));
	assert(in_own_cluster(c_ptr->addr));

	tstop = is_slave(upper) ? c_ptr->highest_slave : c_ptr->highest_node;
	if (tstop > upper)
		tstop = upper;
	for (n_num = lower; n_num <= tstop; n_num++) {
		n_ptr = c_ptr->nodes[n_num];
		if (n_ptr && tipc_node_has_active_links(n_ptr)) {
			buf_copy = skb_copy(buf, GFP_ATOMIC);
			if (buf_copy == NULL)
				break;
			msg_set_destnode(buf_msg(buf_copy), n_ptr->addr);
			tipc_link_send(buf_copy, n_ptr->addr, n_ptr->addr);
		}
	}
	buf_discard(buf);
}