#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {struct sk_buff* next; } ;
struct link {scalar_t__ state; scalar_t__ next_in_no; int checkpoint; int next_out_no; int /*<<< orphan*/  addr; scalar_t__ stale_count; scalar_t__ fsm_msg_cnt; int /*<<< orphan*/ * newest_deferred_in; struct sk_buff* oldest_deferred_in; scalar_t__ deferred_inqueue_sz; scalar_t__ unacked_window; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * first_out; int /*<<< orphan*/ * last_out; scalar_t__ retransm_queue_size; scalar_t__ retransm_queue_head; int /*<<< orphan*/  waiting_ports; struct sk_buff* proto_msg_queue; int /*<<< orphan*/  exp_msg_count; scalar_t__ reset_checkpoint; TYPE_1__* owner; int /*<<< orphan*/  name; int /*<<< orphan*/  b_ptr; int /*<<< orphan*/  peer_session; int /*<<< orphan*/  pmsg; } ;
struct TYPE_3__ {scalar_t__ permit_changeover; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_SESSION ; 
 scalar_t__ RESET_RESET ; 
 scalar_t__ RESET_UNKNOWN ; 
 int /*<<< orphan*/  START_CHANGEOVER ; 
 int /*<<< orphan*/  TIPC_CONS ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg_link_dump () ; 
 int /*<<< orphan*/  dbg_link_state (char*) ; 
 int /*<<< orphan*/  in_own_cluster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_init_max_pkt (struct link*) ; 
 int /*<<< orphan*/  link_release_outqueue (struct link*) ; 
 int /*<<< orphan*/  link_reset_statistics (struct link*) ; 
 int /*<<< orphan*/  link_send_event (int /*<<< orphan*/ ,struct link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int msg_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_session (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tipc_bearer_remove_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cfg_link_event ; 
 int /*<<< orphan*/  tipc_disc_link_event ; 
 int tipc_link_is_active (struct link*) ; 
 int /*<<< orphan*/  tipc_link_wakeup_ports (struct link*,int) ; 
 scalar_t__ tipc_node_has_active_links (TYPE_1__*) ; 
 int /*<<< orphan*/  tipc_node_link_down (TYPE_1__*,struct link*) ; 
 int /*<<< orphan*/  tipc_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void tipc_link_reset(struct link *l_ptr)
{
	struct sk_buff *buf;
	u32 prev_state = l_ptr->state;
	u32 checkpoint = l_ptr->next_in_no;
	int was_active_link = tipc_link_is_active(l_ptr);

	msg_set_session(l_ptr->pmsg, ((msg_session(l_ptr->pmsg) + 1) & 0xffff));

	/* Link is down, accept any session */
	l_ptr->peer_session = INVALID_SESSION;

	/* Prepare for max packet size negotiation */
	link_init_max_pkt(l_ptr);

	l_ptr->state = RESET_UNKNOWN;
	dbg_link_state("Resetting Link\n");

	if ((prev_state == RESET_UNKNOWN) || (prev_state == RESET_RESET))
		return;

	tipc_node_link_down(l_ptr->owner, l_ptr);
	tipc_bearer_remove_dest(l_ptr->b_ptr, l_ptr->addr);
#if 0
	tipc_printf(TIPC_CONS, "\nReset link <%s>\n", l_ptr->name);
	dbg_link_dump();
#endif
	if (was_active_link && tipc_node_has_active_links(l_ptr->owner) &&
	    l_ptr->owner->permit_changeover) {
		l_ptr->reset_checkpoint = checkpoint;
		l_ptr->exp_msg_count = START_CHANGEOVER;
	}

	/* Clean up all queues: */

	link_release_outqueue(l_ptr);
	buf_discard(l_ptr->proto_msg_queue);
	l_ptr->proto_msg_queue = NULL;
	buf = l_ptr->oldest_deferred_in;
	while (buf) {
		struct sk_buff *next = buf->next;
		buf_discard(buf);
		buf = next;
	}
	if (!list_empty(&l_ptr->waiting_ports))
		tipc_link_wakeup_ports(l_ptr, 1);

	l_ptr->retransm_queue_head = 0;
	l_ptr->retransm_queue_size = 0;
	l_ptr->last_out = NULL;
	l_ptr->first_out = NULL;
	l_ptr->next_out = NULL;
	l_ptr->unacked_window = 0;
	l_ptr->checkpoint = 1;
	l_ptr->next_out_no = 1;
	l_ptr->deferred_inqueue_sz = 0;
	l_ptr->oldest_deferred_in = NULL;
	l_ptr->newest_deferred_in = NULL;
	l_ptr->fsm_msg_cnt = 0;
	l_ptr->stale_count = 0;
	link_reset_statistics(l_ptr);

	link_send_event(tipc_cfg_link_event, l_ptr, 0);
	if (!in_own_cluster(l_ptr->addr))
		link_send_event(tipc_disc_link_event, l_ptr, 0);
}