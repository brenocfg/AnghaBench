#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tipc_node {int /*<<< orphan*/  lock; struct link** links; } ;
struct tipc_msg {int dummy; } ;
struct tipc_media_addr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct link {scalar_t__ state; int /*<<< orphan*/  name; int /*<<< orphan*/  started; struct tipc_media_addr media_addr; } ;
struct TYPE_4__ {struct tipc_media_addr addr; } ;
struct bearer {size_t identity; TYPE_2__ publ; TYPE_1__* media; } ;
typedef  int /*<<< orphan*/  media_addr ;
struct TYPE_3__ {int /*<<< orphan*/  (* send_msg ) (struct sk_buff*,TYPE_2__*,struct tipc_media_addr*) ;} ;

/* Variables and functions */
 scalar_t__ DSC_RESP_MSG ; 
 scalar_t__ WORKING_WORKING ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  disc_dupl_alert (struct bearer*,scalar_t__,struct tipc_media_addr*) ; 
 scalar_t__ in_own_cluster (scalar_t__) ; 
 int /*<<< orphan*/  in_scope (scalar_t__,scalar_t__) ; 
 scalar_t__ is_slave (scalar_t__) ; 
 scalar_t__ memcmp (struct tipc_media_addr*,struct tipc_media_addr*,int) ; 
 int /*<<< orphan*/  memcpy (struct tipc_media_addr*,struct tipc_media_addr*,int) ; 
 scalar_t__ msg_bc_netid (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 scalar_t__ msg_dest_domain (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_get_media_addr (struct tipc_msg*,struct tipc_media_addr*) ; 
 scalar_t__ msg_prevnode (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,TYPE_2__*,struct tipc_media_addr*) ; 
 int /*<<< orphan*/  tipc_addr_domain_valid (scalar_t__) ; 
 int /*<<< orphan*/  tipc_addr_node_valid (scalar_t__) ; 
 struct sk_buff* tipc_disc_init_msg (scalar_t__,int,scalar_t__,struct bearer*) ; 
 struct link* tipc_link_create (struct bearer*,scalar_t__,struct tipc_media_addr*) ; 
 scalar_t__ tipc_link_is_up (struct link*) ; 
 int /*<<< orphan*/  tipc_link_reset (struct link*) ; 
 scalar_t__ tipc_net_id ; 
 struct tipc_node* tipc_node_create (scalar_t__) ; 
 struct tipc_node* tipc_node_find (scalar_t__) ; 
 scalar_t__ tipc_own_addr ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

void tipc_disc_recv_msg(struct sk_buff *buf, struct bearer *b_ptr)
{
	struct link *link;
	struct tipc_media_addr media_addr;
	struct tipc_msg *msg = buf_msg(buf);
	u32 dest = msg_dest_domain(msg);
	u32 orig = msg_prevnode(msg);
	u32 net_id = msg_bc_netid(msg);
	u32 type = msg_type(msg);

	msg_get_media_addr(msg,&media_addr);
	msg_dbg(msg, "RECV:");
	buf_discard(buf);

	if (net_id != tipc_net_id)
		return;
	if (!tipc_addr_domain_valid(dest))
		return;
	if (!tipc_addr_node_valid(orig))
		return;
	if (orig == tipc_own_addr) {
		if (memcmp(&media_addr, &b_ptr->publ.addr, sizeof(media_addr)))
			disc_dupl_alert(b_ptr, tipc_own_addr, &media_addr);
		return;
	}
	if (!in_scope(dest, tipc_own_addr))
		return;
	if (is_slave(tipc_own_addr) && is_slave(orig))
		return;
	if (is_slave(orig) && !in_own_cluster(orig))
		return;
	if (in_own_cluster(orig)) {
		/* Always accept link here */
		struct sk_buff *rbuf;
		struct tipc_media_addr *addr;
		struct tipc_node *n_ptr = tipc_node_find(orig);
		int link_fully_up;

		dbg(" in own cluster\n");
		if (n_ptr == NULL) {
			n_ptr = tipc_node_create(orig);
			if (!n_ptr)
				return;
		}
		spin_lock_bh(&n_ptr->lock);
		link = n_ptr->links[b_ptr->identity];
		if (!link) {
			dbg("creating link\n");
			link = tipc_link_create(b_ptr, orig, &media_addr);
			if (!link) {
				spin_unlock_bh(&n_ptr->lock);
				return;
			}
		}
		addr = &link->media_addr;
		if (memcmp(addr, &media_addr, sizeof(*addr))) {
			if (tipc_link_is_up(link) || (!link->started)) {
				disc_dupl_alert(b_ptr, orig, &media_addr);
				spin_unlock_bh(&n_ptr->lock);
				return;
			}
			warn("Resetting link <%s>, peer interface address changed\n",
			     link->name);
			memcpy(addr, &media_addr, sizeof(*addr));
			tipc_link_reset(link);
		}
		link_fully_up = (link->state == WORKING_WORKING);
		spin_unlock_bh(&n_ptr->lock);
		if ((type == DSC_RESP_MSG) || link_fully_up)
			return;
		rbuf = tipc_disc_init_msg(DSC_RESP_MSG, 1, orig, b_ptr);
		if (rbuf != NULL) {
			msg_dbg(buf_msg(rbuf),"SEND:");
			b_ptr->media->send_msg(rbuf, &b_ptr->publ, &media_addr);
			buf_discard(rbuf);
		}
	}
}