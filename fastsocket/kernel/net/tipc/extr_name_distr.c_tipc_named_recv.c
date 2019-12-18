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
struct publication {int /*<<< orphan*/  subscr; } ;
struct distr_item {int /*<<< orphan*/  key; int /*<<< orphan*/  ref; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; int /*<<< orphan*/  upper; } ;
typedef  int /*<<< orphan*/  net_ev_handler ;

/* Variables and functions */
 int ITEM_SIZE ; 
 scalar_t__ PUBLICATION ; 
 int /*<<< orphan*/  TIPC_CLUSTER_SCOPE ; 
 scalar_t__ WITHDRAWAL ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct publication*) ; 
 scalar_t__ msg_data (struct tipc_msg*) ; 
 int msg_data_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 scalar_t__ node_is_down ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct publication* tipc_nametbl_insert_publ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nametbl_lock ; 
 struct publication* tipc_nametbl_remove_publ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nodesub_subscribe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct publication*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nodesub_unsubscribe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void tipc_named_recv(struct sk_buff *buf)
{
	struct publication *publ;
	struct tipc_msg *msg = buf_msg(buf);
	struct distr_item *item = (struct distr_item *)msg_data(msg);
	u32 count = msg_data_sz(msg) / ITEM_SIZE;

	write_lock_bh(&tipc_nametbl_lock);
	while (count--) {
		if (msg_type(msg) == PUBLICATION) {
			dbg("tipc_named_recv: got publication for %u, %u, %u\n",
			    ntohl(item->type), ntohl(item->lower),
			    ntohl(item->upper));
			publ = tipc_nametbl_insert_publ(ntohl(item->type),
							ntohl(item->lower),
							ntohl(item->upper),
							TIPC_CLUSTER_SCOPE,
							msg_orignode(msg),
							ntohl(item->ref),
							ntohl(item->key));
			if (publ) {
				tipc_nodesub_subscribe(&publ->subscr,
						       msg_orignode(msg),
						       publ,
						       (net_ev_handler)node_is_down);
			}
		} else if (msg_type(msg) == WITHDRAWAL) {
			dbg("tipc_named_recv: got withdrawl for %u, %u, %u\n",
			    ntohl(item->type), ntohl(item->lower),
			    ntohl(item->upper));
			publ = tipc_nametbl_remove_publ(ntohl(item->type),
							ntohl(item->lower),
							msg_orignode(msg),
							ntohl(item->ref),
							ntohl(item->key));

			if (publ) {
				tipc_nodesub_unsubscribe(&publ->subscr);
				kfree(publ);
			} else {
				err("Unable to remove publication by node 0x%x\n"
				    "(type=%u, lower=%u, ref=%u, key=%u)\n",
				    msg_orignode(msg),
				    ntohl(item->type), ntohl(item->lower),
				    ntohl(item->ref), ntohl(item->key));
			}
		} else {
			warn("Unrecognized name table message received\n");
		}
		item++;
	}
	write_unlock_bh(&tipc_nametbl_lock);
	buf_discard(buf);
}