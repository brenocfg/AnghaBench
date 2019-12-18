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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  duplicates; int /*<<< orphan*/  deferred_recv; } ;
struct link {int deferred_inqueue_sz; TYPE_1__ stats; int /*<<< orphan*/  newest_deferred_in; int /*<<< orphan*/  oldest_deferred_in; int /*<<< orphan*/  next_in_no; int /*<<< orphan*/  checkpoint; } ;

/* Variables and functions */
 scalar_t__ LINK_PROTOCOL ; 
 int /*<<< orphan*/  STATE_MSG ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  link_recv_proto_msg (struct link*,struct sk_buff*) ; 
 int /*<<< orphan*/  mod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_seqno (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_user (int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_link_defer_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_link_send_proto_msg (struct link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_handle_out_of_seq_msg(struct link *l_ptr,
				       struct sk_buff *buf)
{
	u32 seq_no = msg_seqno(buf_msg(buf));

	if (likely(msg_user(buf_msg(buf)) == LINK_PROTOCOL)) {
		link_recv_proto_msg(l_ptr, buf);
		return;
	}

	dbg("rx OOS msg: seq_no %u, expecting %u (%u)\n",
	    seq_no, mod(l_ptr->next_in_no), l_ptr->next_in_no);

	/* Record OOS packet arrival (force mismatch on next timeout) */

	l_ptr->checkpoint--;

	/*
	 * Discard packet if a duplicate; otherwise add it to deferred queue
	 * and notify peer of gap as per protocol specification
	 */

	if (less(seq_no, mod(l_ptr->next_in_no))) {
		l_ptr->stats.duplicates++;
		buf_discard(buf);
		return;
	}

	if (tipc_link_defer_pkt(&l_ptr->oldest_deferred_in,
				&l_ptr->newest_deferred_in, buf)) {
		l_ptr->deferred_inqueue_sz++;
		l_ptr->stats.deferred_recv++;
		if ((l_ptr->deferred_inqueue_sz % 16) == 1)
			tipc_link_send_proto_msg(l_ptr, STATE_MSG, 0, 0, 0, 0, 0);
	} else
		l_ptr->stats.duplicates++;
}