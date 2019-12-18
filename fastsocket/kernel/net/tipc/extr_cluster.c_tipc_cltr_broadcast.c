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
struct cluster {int highest_node; int highest_slave; struct tipc_node** nodes; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LOWEST_SLAVE ; 
 scalar_t__ TIPC_NET_MODE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  in_own_cluster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct cluster* tipc_cltr_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_link_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_mode ; 
 scalar_t__ tipc_node_has_active_links (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 

void tipc_cltr_broadcast(struct sk_buff *buf)
{
	struct sk_buff *buf_copy;
	struct cluster *c_ptr;
	struct tipc_node *n_ptr;
	u32 n_num;
	u32 tstart;
	u32 tstop;
	u32 node_type;

	if (tipc_mode == TIPC_NET_MODE) {
		c_ptr = tipc_cltr_find(tipc_own_addr);
		assert(in_own_cluster(c_ptr->addr));	/* For now */

		/* Send to standard nodes, then repeat loop sending to slaves */
		tstart = 1;
		tstop = c_ptr->highest_node;
		for (node_type = 1; node_type <= 2; node_type++) {
			for (n_num = tstart; n_num <= tstop; n_num++) {
				n_ptr = c_ptr->nodes[n_num];
				if (n_ptr && tipc_node_has_active_links(n_ptr)) {
					buf_copy = skb_copy(buf, GFP_ATOMIC);
					if (buf_copy == NULL)
						goto exit;
					msg_set_destnode(buf_msg(buf_copy),
							 n_ptr->addr);
					tipc_link_send(buf_copy, n_ptr->addr,
						       n_ptr->addr);
				}
			}
			tstart = LOWEST_SLAVE;
			tstop = c_ptr->highest_slave;
		}
	}
exit:
	buf_discard(buf);
}