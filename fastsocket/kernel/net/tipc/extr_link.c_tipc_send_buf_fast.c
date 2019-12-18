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
typedef  size_t u32 ;
struct tipc_node {struct tipc_node** active_links; } ;
struct sk_buff {int dummy; } ;
struct link {struct link** active_links; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_ERR_NO_NODE ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,struct sk_buff*,struct tipc_node*,size_t) ; 
 scalar_t__ likely (struct tipc_node*) ; 
 int link_send_buf_fast (struct tipc_node*,struct sk_buff*,size_t*) ; 
 int msg_data_sz (int /*<<< orphan*/ ) ; 
 int msg_origport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 int /*<<< orphan*/  tipc_node_lock (struct tipc_node*) ; 
 struct tipc_node* tipc_node_select (size_t,size_t) ; 
 int /*<<< orphan*/  tipc_node_unlock (struct tipc_node*) ; 
 size_t tipc_own_addr ; 
 int tipc_port_recv_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_reject_msg (struct sk_buff*,int /*<<< orphan*/ ) ; 

int tipc_send_buf_fast(struct sk_buff *buf, u32 destnode)
{
	struct link *l_ptr;
	struct tipc_node *n_ptr;
	int res;
	u32 selector = msg_origport(buf_msg(buf)) & 1;
	u32 dummy;

	if (destnode == tipc_own_addr)
		return tipc_port_recv_msg(buf);

	read_lock_bh(&tipc_net_lock);
	n_ptr = tipc_node_select(destnode, selector);
	if (likely(n_ptr)) {
		tipc_node_lock(n_ptr);
		l_ptr = n_ptr->active_links[selector];
		dbg("send_fast: buf %x selected %x, destnode = %x\n",
		    buf, l_ptr, destnode);
		if (likely(l_ptr)) {
			res = link_send_buf_fast(l_ptr, buf, &dummy);
			tipc_node_unlock(n_ptr);
			read_unlock_bh(&tipc_net_lock);
			return res;
		}
		tipc_node_unlock(n_ptr);
	}
	read_unlock_bh(&tipc_net_lock);
	res = msg_data_sz(buf_msg(buf));
	tipc_reject_msg(buf, TIPC_ERR_NO_NODE);
	return res;
}