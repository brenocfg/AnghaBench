#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  nack_sync; int /*<<< orphan*/  gap_to; int /*<<< orphan*/  gap_after; int /*<<< orphan*/  last_in; } ;
struct tipc_node {TYPE_2__ bclink; int /*<<< orphan*/  addr; } ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  bearer; } ;
struct TYPE_6__ {int /*<<< orphan*/  bearer_congs; int /*<<< orphan*/  sent_nacks; } ;
struct TYPE_8__ {TYPE_1__ stats; struct sk_buff* proto_msg_queue; int /*<<< orphan*/  b_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCAST_PROTOCOL ; 
 int /*<<< orphan*/  INT_H_SIZE ; 
 int /*<<< orphan*/  STATE_MSG ; 
 TYPE_5__* bcbearer ; 
 TYPE_3__* bcl ; 
 struct sk_buff* buf_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_init (struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bcast_ack (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bcast_tag (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bcgap_after (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bcgap_to (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_mc_netid (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_bearer_schedule (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ tipc_bearer_send (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_net_id ; 
 int /*<<< orphan*/  tipc_own_tag ; 

__attribute__((used)) static void bclink_send_nack(struct tipc_node *n_ptr)
{
	struct sk_buff *buf;
	struct tipc_msg *msg;

	if (!less(n_ptr->bclink.gap_after, n_ptr->bclink.gap_to))
		return;

	buf = buf_acquire(INT_H_SIZE);
	if (buf) {
		msg = buf_msg(buf);
		msg_init(msg, BCAST_PROTOCOL, STATE_MSG,
			 INT_H_SIZE, n_ptr->addr);
		msg_set_mc_netid(msg, tipc_net_id);
		msg_set_bcast_ack(msg, mod(n_ptr->bclink.last_in));
		msg_set_bcgap_after(msg, n_ptr->bclink.gap_after);
		msg_set_bcgap_to(msg, n_ptr->bclink.gap_to);
		msg_set_bcast_tag(msg, tipc_own_tag);

		if (tipc_bearer_send(&bcbearer->bearer, buf, NULL)) {
			bcl->stats.sent_nacks++;
			buf_discard(buf);
		} else {
			tipc_bearer_schedule(bcl->b_ptr, bcl);
			bcl->proto_msg_queue = buf;
			bcl->stats.bearer_congs++;
		}

		/*
		 * Ensure we doesn't send another NACK msg to the node
		 * until 16 more deferred messages arrive from it
		 * (i.e. helps prevent all nodes from NACK'ing at same time)
		 */

		n_ptr->bclink.nack_sync = tipc_own_tag;
	}
}