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
struct vlan_ethhdr {scalar_t__ h_vlan_proto; int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_id; int /*<<< orphan*/ * flags; scalar_t__ pkt_length; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ l2; } ;
struct qeth_hdr {TYPE_2__ hdr; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ QETH_HEADER_SIZE ; 
 int /*<<< orphan*/  QETH_HEADER_TYPE_LAYER2 ; 
 int /*<<< orphan*/  QETH_LAYER2_FLAG_BROADCAST ; 
 int /*<<< orphan*/  QETH_LAYER2_FLAG_MULTICAST ; 
 int /*<<< orphan*/  QETH_LAYER2_FLAG_UNICAST ; 
 int /*<<< orphan*/  QETH_LAYER2_FLAG_VLAN ; 
 int RTN_BROADCAST ; 
 int RTN_MULTICAST ; 
 scalar_t__ __constant_htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qeth_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void qeth_l2_fill_header(struct qeth_card *card, struct qeth_hdr *hdr,
			struct sk_buff *skb, int ipv, int cast_type)
{
	struct vlan_ethhdr *veth = (struct vlan_ethhdr *)skb_mac_header(skb);

	memset(hdr, 0, sizeof(struct qeth_hdr));
	hdr->hdr.l2.id = QETH_HEADER_TYPE_LAYER2;

	/* set byte byte 3 to casting flags */
	if (cast_type == RTN_MULTICAST)
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_MULTICAST;
	else if (cast_type == RTN_BROADCAST)
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_BROADCAST;
	else
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_UNICAST;

	hdr->hdr.l2.pkt_length = skb->len-QETH_HEADER_SIZE;
	/* VSWITCH relies on the VLAN
	 * information to be present in
	 * the QDIO header */
	if (veth->h_vlan_proto == __constant_htons(ETH_P_8021Q)) {
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_VLAN;
		hdr->hdr.l2.vlan_id = ntohs(veth->h_vlan_TCI);
	}
}