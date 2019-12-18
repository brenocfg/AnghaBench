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
typedef  int /*<<< orphan*/  u32 ;
struct tcphdr {int doff; int /*<<< orphan*/  seq; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rcv_nxt; } ;
struct nes_cm_node {int state; int accept_pend; TYPE_2__* listener; int /*<<< orphan*/  send_entry; TYPE_1__ tcp_cntxt; } ;
struct TYPE_4__ {int /*<<< orphan*/  pend_accepts_cnt; int /*<<< orphan*/  backlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
#define  NES_CM_STATE_CLOSED 139 
#define  NES_CM_STATE_CLOSING 138 
#define  NES_CM_STATE_ESTABLISHED 137 
#define  NES_CM_STATE_FIN_WAIT1 136 
#define  NES_CM_STATE_FIN_WAIT2 135 
#define  NES_CM_STATE_LAST_ACK 134 
#define  NES_CM_STATE_LISTENING 133 
#define  NES_CM_STATE_MPAREQ_RCVD 132 
#define  NES_CM_STATE_MPAREQ_SENT 131 
 int NES_CM_STATE_SYN_RCVD ; 
#define  NES_CM_STATE_SYN_SENT 130 
#define  NES_CM_STATE_TSA 129 
#define  NES_CM_STATE_UNKNOWN 128 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  active_open_err (struct nes_cm_node*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  add_ref_cm_node (struct nes_cm_node*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_retrans_entry (struct nes_cm_node*) ; 
 int /*<<< orphan*/  cm_backlog_drops ; 
 int /*<<< orphan*/  drop_packet (struct sk_buff*) ; 
 int handle_tcp_options (struct nes_cm_node*,struct tcphdr*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  passive_open_err (struct nes_cm_node*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_reset (struct nes_cm_node*,struct sk_buff*) ; 
 int /*<<< orphan*/  send_syn (struct nes_cm_node*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_syn_pkt(struct nes_cm_node *cm_node, struct sk_buff *skb,
			   struct tcphdr *tcph)
{
	int ret;
	u32 inc_sequence;
	int optionsize;

	optionsize = (tcph->doff << 2) - sizeof(struct tcphdr);
	skb_trim(skb, 0);
	inc_sequence = ntohl(tcph->seq);

	switch (cm_node->state) {
	case NES_CM_STATE_SYN_SENT:
	case NES_CM_STATE_MPAREQ_SENT:
		/* Rcvd syn on active open connection*/
		active_open_err(cm_node, skb, 1);
		break;
	case NES_CM_STATE_LISTENING:
		/* Passive OPEN */
		if (atomic_read(&cm_node->listener->pend_accepts_cnt) >
		    cm_node->listener->backlog) {
			nes_debug(NES_DBG_CM, "drop syn due to backlog "
				  "pressure \n");
			cm_backlog_drops++;
			passive_open_err(cm_node, skb, 0);
			break;
		}
		ret = handle_tcp_options(cm_node, tcph, skb, optionsize,
					 1);
		if (ret) {
			passive_open_err(cm_node, skb, 0);
			/* drop pkt */
			break;
		}
		cm_node->tcp_cntxt.rcv_nxt = inc_sequence + 1;
		BUG_ON(cm_node->send_entry);
		cm_node->accept_pend = 1;
		atomic_inc(&cm_node->listener->pend_accepts_cnt);

		cm_node->state = NES_CM_STATE_SYN_RCVD;
		send_syn(cm_node, 1, skb);
		break;
	case NES_CM_STATE_CLOSED:
		cleanup_retrans_entry(cm_node);
		add_ref_cm_node(cm_node);
		send_reset(cm_node, skb);
		break;
	case NES_CM_STATE_TSA:
	case NES_CM_STATE_ESTABLISHED:
	case NES_CM_STATE_FIN_WAIT1:
	case NES_CM_STATE_FIN_WAIT2:
	case NES_CM_STATE_MPAREQ_RCVD:
	case NES_CM_STATE_LAST_ACK:
	case NES_CM_STATE_CLOSING:
	case NES_CM_STATE_UNKNOWN:
	default:
		drop_packet(skb);
		break;
	}
}