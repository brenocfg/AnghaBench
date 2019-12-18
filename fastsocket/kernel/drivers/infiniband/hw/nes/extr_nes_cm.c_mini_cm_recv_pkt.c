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
struct tcphdr {int /*<<< orphan*/  fin; int /*<<< orphan*/  rst; scalar_t__ ack; int /*<<< orphan*/  syn; int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct nes_vnic {int dummy; } ;
struct nes_cm_node {scalar_t__ state; TYPE_1__* nesqp; } ;
struct nes_cm_listener {int /*<<< orphan*/  ref_count; scalar_t__ conn_type; int /*<<< orphan*/ * cm_id; } ;
struct nes_cm_info {scalar_t__ conn_type; int /*<<< orphan*/ * cm_id; void* loc_port; void* loc_addr; void* rem_addr; void* rem_port; } ;
struct nes_cm_core {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tot_len; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ pau_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_CM_LISTENER_ACTIVE_STATE ; 
 scalar_t__ NES_CM_STATE_LISTENING ; 
 scalar_t__ NES_CM_STATE_TSA ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  add_ref_cm_node (struct nes_cm_node*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_accel_dropped_pkts ; 
 int /*<<< orphan*/  cm_packets_dropped ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct nes_cm_listener* find_listener (struct nes_cm_core*,void*,void*,int /*<<< orphan*/ ) ; 
 struct nes_cm_node* find_node (struct nes_cm_core*,void*,void*,void*,void*) ; 
 struct nes_cm_node* make_cm_node (struct nes_cm_core*,struct nes_vnic*,struct nes_cm_info*,struct nes_cm_listener*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nes_queue_mgt_skbs (struct sk_buff*,struct nes_vnic*,TYPE_1__*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_packet (struct nes_cm_node*,struct sk_buff*,struct nes_cm_core*) ; 
 int /*<<< orphan*/  rem_ref_cm_node (struct nes_cm_core*,struct nes_cm_node*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 

__attribute__((used)) static int mini_cm_recv_pkt(struct nes_cm_core *cm_core,
			    struct nes_vnic *nesvnic, struct sk_buff *skb)
{
	struct nes_cm_node *cm_node = NULL;
	struct nes_cm_listener *listener = NULL;
	struct iphdr *iph;
	struct tcphdr *tcph;
	struct nes_cm_info nfo;
	int skb_handled = 1;
	__be32 tmp_daddr, tmp_saddr;

	if (!skb)
		return 0;
	if (skb->len < sizeof(struct iphdr) + sizeof(struct tcphdr))
		return 0;

	iph = (struct iphdr *)skb->data;
	tcph = (struct tcphdr *)(skb->data + sizeof(struct iphdr));

	nfo.loc_addr = ntohl(iph->daddr);
	nfo.loc_port = ntohs(tcph->dest);
	nfo.rem_addr = ntohl(iph->saddr);
	nfo.rem_port = ntohs(tcph->source);

	tmp_daddr = cpu_to_be32(iph->daddr);
	tmp_saddr = cpu_to_be32(iph->saddr);

	nes_debug(NES_DBG_CM, "Received packet: dest=%pI4:0x%04X src=%pI4:0x%04X\n",
		  &tmp_daddr, tcph->dest, &tmp_saddr, tcph->source);

	do {
		cm_node = find_node(cm_core,
				    nfo.rem_port, nfo.rem_addr,
				    nfo.loc_port, nfo.loc_addr);

		if (!cm_node) {
			/* Only type of packet accepted are for */
			/* the PASSIVE open (syn only) */
			if ((!tcph->syn) || (tcph->ack)) {
				skb_handled = 0;
				break;
			}
			listener = find_listener(cm_core, nfo.loc_addr,
						 nfo.loc_port,
						 NES_CM_LISTENER_ACTIVE_STATE);
			if (!listener) {
				nfo.cm_id = NULL;
				nfo.conn_type = 0;
				nes_debug(NES_DBG_CM, "Unable to find listener for the pkt\n");
				skb_handled = 0;
				break;
			}
			nfo.cm_id = listener->cm_id;
			nfo.conn_type = listener->conn_type;
			cm_node = make_cm_node(cm_core, nesvnic, &nfo,
					       listener);
			if (!cm_node) {
				nes_debug(NES_DBG_CM, "Unable to allocate "
					  "node\n");
				cm_packets_dropped++;
				atomic_dec(&listener->ref_count);
				dev_kfree_skb_any(skb);
				break;
			}
			if (!tcph->rst && !tcph->fin) {
				cm_node->state = NES_CM_STATE_LISTENING;
			} else {
				cm_packets_dropped++;
				rem_ref_cm_node(cm_core, cm_node);
				dev_kfree_skb_any(skb);
				break;
			}
			add_ref_cm_node(cm_node);
		} else if (cm_node->state == NES_CM_STATE_TSA) {
			if (cm_node->nesqp->pau_mode)
				nes_queue_mgt_skbs(skb, nesvnic, cm_node->nesqp);
			else {
				rem_ref_cm_node(cm_core, cm_node);
				atomic_inc(&cm_accel_dropped_pkts);
				dev_kfree_skb_any(skb);
			}
			break;
		}
		skb_reset_network_header(skb);
		skb_set_transport_header(skb, sizeof(*tcph));
		skb->len = ntohs(iph->tot_len);
		process_packet(cm_node, skb, cm_core);
		rem_ref_cm_node(cm_core, cm_node);
	} while (0);
	return skb_handled;
}