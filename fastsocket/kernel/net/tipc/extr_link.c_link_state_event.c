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
typedef  int u32 ;
struct link {int continuity_interval; int started; int state; int /*<<< orphan*/  fsm_msg_cnt; TYPE_1__* owner; int /*<<< orphan*/  name; int /*<<< orphan*/  abort_limit; int /*<<< orphan*/  next_in_no; int /*<<< orphan*/  checkpoint; int /*<<< orphan*/  max_pkt_target; int /*<<< orphan*/  max_pkt; } ;
struct TYPE_2__ {struct link** active_links; } ;

/* Variables and functions */
#define  ACTIVATE_MSG 136 
#define  RESET_MSG 135 
#define  RESET_RESET 134 
#define  RESET_UNKNOWN 133 
#define  STARTING_EVT 132 
 int const STATE_MSG ; 
#define  TIMEOUT_EVT 131 
#define  TRAFFIC_MSG_EVT 130 
#define  WORKING_UNKNOWN 129 
#define  WORKING_WORKING 128 
 int /*<<< orphan*/  dbg_link (char*,...) ; 
 int /*<<< orphan*/  err (char*,int,...) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_activate (struct link*) ; 
 scalar_t__ link_blocked (struct link*) ; 
 int /*<<< orphan*/  link_set_timer (struct link*,int) ; 
 int /*<<< orphan*/  link_working_unknown (struct link*) ; 
 int /*<<< orphan*/  tipc_bclink_acks_missing (TYPE_1__*) ; 
 int /*<<< orphan*/  tipc_link_reset (struct link*) ; 
 int /*<<< orphan*/  tipc_link_send_proto_msg (struct link*,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_state_event(struct link *l_ptr, unsigned event)
{
	struct link *other;
	u32 cont_intv = l_ptr->continuity_interval;

	if (!l_ptr->started && (event != STARTING_EVT))
		return;		/* Not yet. */

	if (link_blocked(l_ptr)) {
		if (event == TIMEOUT_EVT) {
			link_set_timer(l_ptr, cont_intv);
		}
		return;	  /* Changeover going on */
	}
	dbg_link("STATE_EV: <%s> ", l_ptr->name);

	switch (l_ptr->state) {
	case WORKING_WORKING:
		dbg_link("WW/");
		switch (event) {
		case TRAFFIC_MSG_EVT:
			dbg_link("TRF-");
			/* fall through */
		case ACTIVATE_MSG:
			dbg_link("ACT\n");
			break;
		case TIMEOUT_EVT:
			dbg_link("TIM ");
			if (l_ptr->next_in_no != l_ptr->checkpoint) {
				l_ptr->checkpoint = l_ptr->next_in_no;
				if (tipc_bclink_acks_missing(l_ptr->owner)) {
					tipc_link_send_proto_msg(l_ptr, STATE_MSG,
								 0, 0, 0, 0, 0);
					l_ptr->fsm_msg_cnt++;
				} else if (l_ptr->max_pkt < l_ptr->max_pkt_target) {
					tipc_link_send_proto_msg(l_ptr, STATE_MSG,
								 1, 0, 0, 0, 0);
					l_ptr->fsm_msg_cnt++;
				}
				link_set_timer(l_ptr, cont_intv);
				break;
			}
			dbg_link(" -> WU\n");
			l_ptr->state = WORKING_UNKNOWN;
			l_ptr->fsm_msg_cnt = 0;
			tipc_link_send_proto_msg(l_ptr, STATE_MSG, 1, 0, 0, 0, 0);
			l_ptr->fsm_msg_cnt++;
			link_set_timer(l_ptr, cont_intv / 4);
			break;
		case RESET_MSG:
			dbg_link("RES -> RR\n");
			info("Resetting link <%s>, requested by peer\n",
			     l_ptr->name);
			tipc_link_reset(l_ptr);
			l_ptr->state = RESET_RESET;
			l_ptr->fsm_msg_cnt = 0;
			tipc_link_send_proto_msg(l_ptr, ACTIVATE_MSG, 0, 0, 0, 0, 0);
			l_ptr->fsm_msg_cnt++;
			link_set_timer(l_ptr, cont_intv);
			break;
		default:
			err("Unknown link event %u in WW state\n", event);
		}
		break;
	case WORKING_UNKNOWN:
		dbg_link("WU/");
		switch (event) {
		case TRAFFIC_MSG_EVT:
			dbg_link("TRF-");
		case ACTIVATE_MSG:
			dbg_link("ACT -> WW\n");
			l_ptr->state = WORKING_WORKING;
			l_ptr->fsm_msg_cnt = 0;
			link_set_timer(l_ptr, cont_intv);
			break;
		case RESET_MSG:
			dbg_link("RES -> RR\n");
			info("Resetting link <%s>, requested by peer "
			     "while probing\n", l_ptr->name);
			tipc_link_reset(l_ptr);
			l_ptr->state = RESET_RESET;
			l_ptr->fsm_msg_cnt = 0;
			tipc_link_send_proto_msg(l_ptr, ACTIVATE_MSG, 0, 0, 0, 0, 0);
			l_ptr->fsm_msg_cnt++;
			link_set_timer(l_ptr, cont_intv);
			break;
		case TIMEOUT_EVT:
			dbg_link("TIM ");
			if (l_ptr->next_in_no != l_ptr->checkpoint) {
				dbg_link("-> WW \n");
				l_ptr->state = WORKING_WORKING;
				l_ptr->fsm_msg_cnt = 0;
				l_ptr->checkpoint = l_ptr->next_in_no;
				if (tipc_bclink_acks_missing(l_ptr->owner)) {
					tipc_link_send_proto_msg(l_ptr, STATE_MSG,
								 0, 0, 0, 0, 0);
					l_ptr->fsm_msg_cnt++;
				}
				link_set_timer(l_ptr, cont_intv);
			} else if (l_ptr->fsm_msg_cnt < l_ptr->abort_limit) {
				dbg_link("Probing %u/%u,timer = %u ms)\n",
					 l_ptr->fsm_msg_cnt, l_ptr->abort_limit,
					 cont_intv / 4);
				tipc_link_send_proto_msg(l_ptr, STATE_MSG,
							 1, 0, 0, 0, 0);
				l_ptr->fsm_msg_cnt++;
				link_set_timer(l_ptr, cont_intv / 4);
			} else {	/* Link has failed */
				dbg_link("-> RU (%u probes unanswered)\n",
					 l_ptr->fsm_msg_cnt);
				warn("Resetting link <%s>, peer not responding\n",
				     l_ptr->name);
				tipc_link_reset(l_ptr);
				l_ptr->state = RESET_UNKNOWN;
				l_ptr->fsm_msg_cnt = 0;
				tipc_link_send_proto_msg(l_ptr, RESET_MSG,
							 0, 0, 0, 0, 0);
				l_ptr->fsm_msg_cnt++;
				link_set_timer(l_ptr, cont_intv);
			}
			break;
		default:
			err("Unknown link event %u in WU state\n", event);
		}
		break;
	case RESET_UNKNOWN:
		dbg_link("RU/");
		switch (event) {
		case TRAFFIC_MSG_EVT:
			dbg_link("TRF-\n");
			break;
		case ACTIVATE_MSG:
			other = l_ptr->owner->active_links[0];
			if (other && link_working_unknown(other)) {
				dbg_link("ACT\n");
				break;
			}
			dbg_link("ACT -> WW\n");
			l_ptr->state = WORKING_WORKING;
			l_ptr->fsm_msg_cnt = 0;
			link_activate(l_ptr);
			tipc_link_send_proto_msg(l_ptr, STATE_MSG, 1, 0, 0, 0, 0);
			l_ptr->fsm_msg_cnt++;
			link_set_timer(l_ptr, cont_intv);
			break;
		case RESET_MSG:
			dbg_link("RES \n");
			dbg_link(" -> RR\n");
			l_ptr->state = RESET_RESET;
			l_ptr->fsm_msg_cnt = 0;
			tipc_link_send_proto_msg(l_ptr, ACTIVATE_MSG, 1, 0, 0, 0, 0);
			l_ptr->fsm_msg_cnt++;
			link_set_timer(l_ptr, cont_intv);
			break;
		case STARTING_EVT:
			dbg_link("START-");
			l_ptr->started = 1;
			/* fall through */
		case TIMEOUT_EVT:
			dbg_link("TIM \n");
			tipc_link_send_proto_msg(l_ptr, RESET_MSG, 0, 0, 0, 0, 0);
			l_ptr->fsm_msg_cnt++;
			link_set_timer(l_ptr, cont_intv);
			break;
		default:
			err("Unknown link event %u in RU state\n", event);
		}
		break;
	case RESET_RESET:
		dbg_link("RR/ ");
		switch (event) {
		case TRAFFIC_MSG_EVT:
			dbg_link("TRF-");
			/* fall through */
		case ACTIVATE_MSG:
			other = l_ptr->owner->active_links[0];
			if (other && link_working_unknown(other)) {
				dbg_link("ACT\n");
				break;
			}
			dbg_link("ACT -> WW\n");
			l_ptr->state = WORKING_WORKING;
			l_ptr->fsm_msg_cnt = 0;
			link_activate(l_ptr);
			tipc_link_send_proto_msg(l_ptr, STATE_MSG, 1, 0, 0, 0, 0);
			l_ptr->fsm_msg_cnt++;
			link_set_timer(l_ptr, cont_intv);
			break;
		case RESET_MSG:
			dbg_link("RES\n");
			break;
		case TIMEOUT_EVT:
			dbg_link("TIM\n");
			tipc_link_send_proto_msg(l_ptr, ACTIVATE_MSG, 0, 0, 0, 0, 0);
			l_ptr->fsm_msg_cnt++;
			link_set_timer(l_ptr, cont_intv);
			dbg_link("fsm_msg_cnt %u\n", l_ptr->fsm_msg_cnt);
			break;
		default:
			err("Unknown link event %u in RR state\n", event);
		}
		break;
	default:
		err("Unknown link state %u/%u\n", l_ptr->state, event);
	}
}