#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  acked; } ;
struct tipc_node {TYPE_1__ bclink; } ;
struct sk_buff {struct sk_buff* next; } ;
struct TYPE_6__ {int next_out; int /*<<< orphan*/  waiting_ports; int /*<<< orphan*/  out_queue_size; struct sk_buff* first_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  bc_lock ; 
 scalar_t__ bcbuf_acks (struct sk_buff*) ; 
 int /*<<< orphan*/  bcbuf_decr_acks (struct sk_buff*) ; 
 TYPE_2__* bcl ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_seqno (struct sk_buff*) ; 
 scalar_t__ less_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_link_push_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  tipc_link_wakeup_ports (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void tipc_bclink_acknowledge(struct tipc_node *n_ptr, u32 acked)
{
	struct sk_buff *crs;
	struct sk_buff *next;
	unsigned int released = 0;

	if (less_eq(acked, n_ptr->bclink.acked))
		return;

	spin_lock_bh(&bc_lock);

	/* Skip over packets that node has previously acknowledged */

	crs = bcl->first_out;
	while (crs && less_eq(buf_seqno(crs), n_ptr->bclink.acked)) {
		crs = crs->next;
	}

	/* Update packets that node is now acknowledging */

	while (crs && less_eq(buf_seqno(crs), acked)) {
		next = crs->next;
		bcbuf_decr_acks(crs);
		if (bcbuf_acks(crs) == 0) {
			bcl->first_out = next;
			bcl->out_queue_size--;
			buf_discard(crs);
			released = 1;
		}
		crs = next;
	}
	n_ptr->bclink.acked = acked;

	/* Try resolving broadcast link congestion, if necessary */

	if (unlikely(bcl->next_out))
		tipc_link_push_queue(bcl);
	if (unlikely(released && !list_empty(&bcl->waiting_ports)))
		tipc_link_wakeup_ports(bcl, 0);
	spin_unlock_bh(&bc_lock);
}