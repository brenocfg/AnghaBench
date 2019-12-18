#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tipc_portid {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct tipc_msg {int dummy; } ;
struct TYPE_2__ {int connected; int /*<<< orphan*/  max_pkt; int /*<<< orphan*/  ref; struct tipc_msg phdr; scalar_t__ published; } ;
struct port {TYPE_1__ publ; int /*<<< orphan*/  subscription; int /*<<< orphan*/  probing_interval; int /*<<< orphan*/  timer; int /*<<< orphan*/  probing_state; } ;
typedef  int /*<<< orphan*/  net_ev_handler ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIRMED ; 
 int EINVAL ; 
 int /*<<< orphan*/  LONG_H_SIZE ; 
 int /*<<< orphan*/  PROBING_INTERVAL ; 
 int /*<<< orphan*/  SHORT_H_SIZE ; 
 int /*<<< orphan*/  TIPC_CONN_MSG ; 
 int /*<<< orphan*/  k_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  may_route (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_hdr_sz (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_orignode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_transp_seqno (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 scalar_t__ port_handle_node_down ; 
 int /*<<< orphan*/  tipc_link_get_max_pkt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tipc_nodesub_subscribe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 struct port* tipc_port_lock (scalar_t__) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

int tipc_connect2port(u32 ref, struct tipc_portid const *peer)
{
	struct port *p_ptr;
	struct tipc_msg *msg;
	int res = -EINVAL;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return -EINVAL;
	if (p_ptr->publ.published || p_ptr->publ.connected)
		goto exit;
	if (!peer->ref)
		goto exit;

	msg = &p_ptr->publ.phdr;
	msg_set_destnode(msg, peer->node);
	msg_set_destport(msg, peer->ref);
	msg_set_orignode(msg, tipc_own_addr);
	msg_set_origport(msg, p_ptr->publ.ref);
	msg_set_transp_seqno(msg, 42);
	msg_set_type(msg, TIPC_CONN_MSG);
	if (!may_route(peer->node))
		msg_set_hdr_sz(msg, SHORT_H_SIZE);
	else
		msg_set_hdr_sz(msg, LONG_H_SIZE);

	p_ptr->probing_interval = PROBING_INTERVAL;
	p_ptr->probing_state = CONFIRMED;
	p_ptr->publ.connected = 1;
	k_start_timer(&p_ptr->timer, p_ptr->probing_interval);

	tipc_nodesub_subscribe(&p_ptr->subscription,peer->node,
			  (void *)(unsigned long)ref,
			  (net_ev_handler)port_handle_node_down);
	res = 0;
exit:
	tipc_port_unlock(p_ptr);
	p_ptr->publ.max_pkt = tipc_link_get_max_pkt(peer->node, ref);
	return res;
}