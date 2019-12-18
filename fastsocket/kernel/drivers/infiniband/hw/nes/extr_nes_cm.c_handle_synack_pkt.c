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
typedef  void* u32 ;
struct tcphdr {int doff; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  seq; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {void* loc_seq_num; int /*<<< orphan*/  rcv_nxt; void* rem_ack_num; } ;
struct nes_cm_node {int state; TYPE_1__ tcp_cntxt; } ;

/* Variables and functions */
#define  NES_CM_STATE_CLOSED 139 
#define  NES_CM_STATE_CLOSING 138 
#define  NES_CM_STATE_ESTABLISHED 137 
#define  NES_CM_STATE_FIN_WAIT1 136 
#define  NES_CM_STATE_FIN_WAIT2 135 
#define  NES_CM_STATE_LAST_ACK 134 
#define  NES_CM_STATE_LISTENING 133 
#define  NES_CM_STATE_MPAREQ_RCVD 132 
#define  NES_CM_STATE_MPAREQ_SENT 131 
#define  NES_CM_STATE_SYN_SENT 130 
#define  NES_CM_STATE_TSA 129 
#define  NES_CM_STATE_UNKNOWN 128 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  add_ref_cm_node (struct nes_cm_node*) ; 
 int /*<<< orphan*/  check_syn (struct nes_cm_node*,struct tcphdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  cleanup_retrans_entry (struct nes_cm_node*) ; 
 int /*<<< orphan*/  drop_packet (struct sk_buff*) ; 
 int handle_tcp_options (struct nes_cm_node*,struct tcphdr*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,struct nes_cm_node*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  passive_open_err (struct nes_cm_node*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  send_mpa_request (struct nes_cm_node*,struct sk_buff*) ; 
 int /*<<< orphan*/  send_reset (struct nes_cm_node*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_synack_pkt(struct nes_cm_node *cm_node, struct sk_buff *skb,
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
		cleanup_retrans_entry(cm_node);
		/* active open */
		if (check_syn(cm_node, tcph, skb))
			return;
		cm_node->tcp_cntxt.rem_ack_num = ntohl(tcph->ack_seq);
		/* setup options */
		ret = handle_tcp_options(cm_node, tcph, skb, optionsize, 0);
		if (ret) {
			nes_debug(NES_DBG_CM, "cm_node=%p tcp_options failed\n",
				  cm_node);
			break;
		}
		cleanup_retrans_entry(cm_node);
		cm_node->tcp_cntxt.rcv_nxt = inc_sequence + 1;
		send_mpa_request(cm_node, skb);
		cm_node->state = NES_CM_STATE_MPAREQ_SENT;
		break;
	case NES_CM_STATE_MPAREQ_RCVD:
		/* passive open, so should not be here */
		passive_open_err(cm_node, skb, 1);
		break;
	case NES_CM_STATE_LISTENING:
		cm_node->tcp_cntxt.loc_seq_num = ntohl(tcph->ack_seq);
		cleanup_retrans_entry(cm_node);
		cm_node->state = NES_CM_STATE_CLOSED;
		send_reset(cm_node, skb);
		break;
	case NES_CM_STATE_CLOSED:
		cm_node->tcp_cntxt.loc_seq_num = ntohl(tcph->ack_seq);
		cleanup_retrans_entry(cm_node);
		add_ref_cm_node(cm_node);
		send_reset(cm_node, skb);
		break;
	case NES_CM_STATE_ESTABLISHED:
	case NES_CM_STATE_FIN_WAIT1:
	case NES_CM_STATE_FIN_WAIT2:
	case NES_CM_STATE_LAST_ACK:
	case NES_CM_STATE_TSA:
	case NES_CM_STATE_CLOSING:
	case NES_CM_STATE_UNKNOWN:
	case NES_CM_STATE_MPAREQ_SENT:
	default:
		drop_packet(skb);
		break;
	}
}