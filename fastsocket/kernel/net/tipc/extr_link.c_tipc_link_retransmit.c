#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {struct sk_buff* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  bearer_congs; int /*<<< orphan*/  retransmitted; } ;
struct link {scalar_t__ last_retransmitted; int stale_count; void* retransm_queue_size; void* retransm_queue_head; TYPE_3__ stats; int /*<<< orphan*/  b_ptr; int /*<<< orphan*/  media_addr; TYPE_2__* owner; scalar_t__ next_in_no; struct sk_buff* next_out; } ;
struct TYPE_4__ {int /*<<< orphan*/  last_in; } ;
struct TYPE_5__ {TYPE_1__ bclink; } ;

/* Variables and functions */
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,void*,struct link*) ; 
 int /*<<< orphan*/  dbg_print_link (struct link*,char*) ; 
 int /*<<< orphan*/  link_retransmit_failure (struct link*,struct sk_buff*) ; 
 int /*<<< orphan*/  mod (scalar_t__) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 scalar_t__ msg_seqno (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_ack (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bcast_ack (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 scalar_t__ tipc_bearer_congested (int /*<<< orphan*/ ,struct link*) ; 
 int /*<<< orphan*/  tipc_bearer_schedule (int /*<<< orphan*/ ,struct link*) ; 
 scalar_t__ tipc_bearer_send (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 

void tipc_link_retransmit(struct link *l_ptr, struct sk_buff *buf,
			  u32 retransmits)
{
	struct tipc_msg *msg;

	if (!buf)
		return;

	msg = buf_msg(buf);

	dbg("Retransmitting %u in link %x\n", retransmits, l_ptr);

	if (tipc_bearer_congested(l_ptr->b_ptr, l_ptr)) {
		if (!skb_cloned(buf)) {
			msg_dbg(msg, ">NO_RETR->BCONG>");
			dbg_print_link(l_ptr, "   ");
			l_ptr->retransm_queue_head = msg_seqno(msg);
			l_ptr->retransm_queue_size = retransmits;
			return;
		} else {
			/* Don't retransmit if driver already has the buffer */
		}
	} else {
		/* Detect repeated retransmit failures on uncongested bearer */

		if (l_ptr->last_retransmitted == msg_seqno(msg)) {
			if (++l_ptr->stale_count > 100) {
				link_retransmit_failure(l_ptr, buf);
				return;
			}
		} else {
			l_ptr->last_retransmitted = msg_seqno(msg);
			l_ptr->stale_count = 1;
		}
	}

	while (retransmits && (buf != l_ptr->next_out) && buf && !skb_cloned(buf)) {
		msg = buf_msg(buf);
		msg_set_ack(msg, mod(l_ptr->next_in_no - 1));
		msg_set_bcast_ack(msg, l_ptr->owner->bclink.last_in);
		if (tipc_bearer_send(l_ptr->b_ptr, buf, &l_ptr->media_addr)) {
			msg_dbg(buf_msg(buf), ">RETR>");
			buf = buf->next;
			retransmits--;
			l_ptr->stats.retransmitted++;
		} else {
			tipc_bearer_schedule(l_ptr->b_ptr, l_ptr);
			l_ptr->stats.bearer_congs++;
			l_ptr->retransm_queue_head = msg_seqno(buf_msg(buf));
			l_ptr->retransm_queue_size = retransmits;
			return;
		}
	}

	l_ptr->retransm_queue_head = l_ptr->retransm_queue_size = 0;
}