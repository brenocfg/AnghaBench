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
typedef  void* u32 ;
struct tcphdr {int doff; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  seq; } ;
struct sk_buff {int len; } ;
struct TYPE_3__ {int /*<<< orphan*/  rcv_nxt; void* rem_ack_num; } ;
struct nes_cm_node {int state; int /*<<< orphan*/  cm_core; TYPE_2__* cm_id; TYPE_1__ tcp_cntxt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* rem_ref ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  NES_CM_STATE_CLOSED 140 
#define  NES_CM_STATE_CLOSING 139 
#define  NES_CM_STATE_ESTABLISHED 138 
#define  NES_CM_STATE_FIN_WAIT1 137 
#define  NES_CM_STATE_FIN_WAIT2 136 
#define  NES_CM_STATE_LAST_ACK 135 
#define  NES_CM_STATE_LISTENING 134 
#define  NES_CM_STATE_MPAREQ_RCVD 133 
#define  NES_CM_STATE_MPAREQ_SENT 132 
#define  NES_CM_STATE_SYN_RCVD 131 
#define  NES_CM_STATE_SYN_SENT 130 
#define  NES_CM_STATE_TSA 129 
#define  NES_CM_STATE_UNKNOWN 128 
 int /*<<< orphan*/  add_ref_cm_node (struct nes_cm_node*) ; 
 scalar_t__ check_seq (struct nes_cm_node*,struct tcphdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  cleanup_retrans_entry (struct nes_cm_node*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  drop_packet (struct sk_buff*) ; 
 int /*<<< orphan*/  handle_rcv_mpa (struct nes_cm_node*,struct sk_buff*) ; 
 int handle_tcp_options (struct nes_cm_node*,struct tcphdr*,struct sk_buff*,int,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rem_ref_cm_node (int /*<<< orphan*/ ,struct nes_cm_node*) ; 
 int /*<<< orphan*/  send_reset (struct nes_cm_node*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int handle_ack_pkt(struct nes_cm_node *cm_node, struct sk_buff *skb,
			  struct tcphdr *tcph)
{
	int datasize = 0;
	u32 inc_sequence;
	int ret = 0;
	int optionsize;

	optionsize = (tcph->doff << 2) - sizeof(struct tcphdr);

	if (check_seq(cm_node, tcph, skb))
		return -EINVAL;

	skb_pull(skb, tcph->doff << 2);
	inc_sequence = ntohl(tcph->seq);
	datasize = skb->len;
	switch (cm_node->state) {
	case NES_CM_STATE_SYN_RCVD:
		/* Passive OPEN */
		cleanup_retrans_entry(cm_node);
		ret = handle_tcp_options(cm_node, tcph, skb, optionsize, 1);
		if (ret)
			break;
		cm_node->tcp_cntxt.rem_ack_num = ntohl(tcph->ack_seq);
		cm_node->state = NES_CM_STATE_ESTABLISHED;
		if (datasize) {
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			handle_rcv_mpa(cm_node, skb);
		} else { /* rcvd ACK only */
			dev_kfree_skb_any(skb);
		}
		break;
	case NES_CM_STATE_ESTABLISHED:
		/* Passive OPEN */
		cleanup_retrans_entry(cm_node);
		if (datasize) {
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			handle_rcv_mpa(cm_node, skb);
		} else {
			drop_packet(skb);
		}
		break;
	case NES_CM_STATE_MPAREQ_SENT:
		cm_node->tcp_cntxt.rem_ack_num = ntohl(tcph->ack_seq);
		if (datasize) {
			cm_node->tcp_cntxt.rcv_nxt = inc_sequence + datasize;
			handle_rcv_mpa(cm_node, skb);
		} else { /* Could be just an ack pkt.. */
			dev_kfree_skb_any(skb);
		}
		break;
	case NES_CM_STATE_LISTENING:
		cleanup_retrans_entry(cm_node);
		cm_node->state = NES_CM_STATE_CLOSED;
		send_reset(cm_node, skb);
		break;
	case NES_CM_STATE_CLOSED:
		cleanup_retrans_entry(cm_node);
		add_ref_cm_node(cm_node);
		send_reset(cm_node, skb);
		break;
	case NES_CM_STATE_LAST_ACK:
	case NES_CM_STATE_CLOSING:
		cleanup_retrans_entry(cm_node);
		cm_node->state = NES_CM_STATE_CLOSED;
		cm_node->cm_id->rem_ref(cm_node->cm_id);
		rem_ref_cm_node(cm_node->cm_core, cm_node);
		drop_packet(skb);
		break;
	case NES_CM_STATE_FIN_WAIT1:
		cleanup_retrans_entry(cm_node);
		drop_packet(skb);
		cm_node->state = NES_CM_STATE_FIN_WAIT2;
		break;
	case NES_CM_STATE_SYN_SENT:
	case NES_CM_STATE_FIN_WAIT2:
	case NES_CM_STATE_TSA:
	case NES_CM_STATE_MPAREQ_RCVD:
	case NES_CM_STATE_UNKNOWN:
	default:
		cleanup_retrans_entry(cm_node);
		drop_packet(skb);
		break;
	}
	return ret;
}