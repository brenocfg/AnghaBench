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
struct tcphdr {scalar_t__ fin; scalar_t__ ack; scalar_t__ syn; scalar_t__ rst; } ;
struct sk_buff {int dummy; } ;
struct nes_cm_node {int /*<<< orphan*/  state; } ;
struct nes_cm_core {int dummy; } ;
typedef  enum nes_tcpip_pkt_type { ____Placeholder_nes_tcpip_pkt_type } nes_tcpip_pkt_type ;
struct TYPE_2__ {int ihl; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_CM ; 
#define  NES_PKT_TYPE_ACK 131 
#define  NES_PKT_TYPE_RST 130 
#define  NES_PKT_TYPE_SYN 129 
#define  NES_PKT_TYPE_SYNACK 128 
 int NES_PKT_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  check_seq (struct nes_cm_node*,struct tcphdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  drop_packet (struct sk_buff*) ; 
 int handle_ack_pkt (struct nes_cm_node*,struct sk_buff*,struct tcphdr*) ; 
 int /*<<< orphan*/  handle_fin_pkt (struct nes_cm_node*) ; 
 int /*<<< orphan*/  handle_rst_pkt (struct nes_cm_node*,struct sk_buff*,struct tcphdr*) ; 
 int /*<<< orphan*/  handle_syn_pkt (struct nes_cm_node*,struct sk_buff*,struct tcphdr*) ; 
 int /*<<< orphan*/  handle_synack_pkt (struct nes_cm_node*,struct sk_buff*,struct tcphdr*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,struct nes_cm_node*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void process_packet(struct nes_cm_node *cm_node, struct sk_buff *skb,
			   struct nes_cm_core *cm_core)
{
	enum nes_tcpip_pkt_type pkt_type = NES_PKT_TYPE_UNKNOWN;
	struct tcphdr *tcph = tcp_hdr(skb);
	u32 fin_set = 0;
	int ret = 0;

	skb_pull(skb, ip_hdr(skb)->ihl << 2);

	nes_debug(NES_DBG_CM, "process_packet: cm_node=%p state =%d syn=%d "
		  "ack=%d rst=%d fin=%d\n", cm_node, cm_node->state, tcph->syn,
		  tcph->ack, tcph->rst, tcph->fin);

	if (tcph->rst) {
		pkt_type = NES_PKT_TYPE_RST;
	} else if (tcph->syn) {
		pkt_type = NES_PKT_TYPE_SYN;
		if (tcph->ack)
			pkt_type = NES_PKT_TYPE_SYNACK;
	} else if (tcph->ack) {
		pkt_type = NES_PKT_TYPE_ACK;
	}
	if (tcph->fin)
		fin_set = 1;

	switch (pkt_type) {
	case NES_PKT_TYPE_SYN:
		handle_syn_pkt(cm_node, skb, tcph);
		break;
	case NES_PKT_TYPE_SYNACK:
		handle_synack_pkt(cm_node, skb, tcph);
		break;
	case NES_PKT_TYPE_ACK:
		ret = handle_ack_pkt(cm_node, skb, tcph);
		if (fin_set && !ret)
			handle_fin_pkt(cm_node);
		break;
	case NES_PKT_TYPE_RST:
		handle_rst_pkt(cm_node, skb, tcph);
		break;
	default:
		if ((fin_set) && (!check_seq(cm_node, tcph, skb)))
			handle_fin_pkt(cm_node);
		drop_packet(skb);
		break;
	}
}