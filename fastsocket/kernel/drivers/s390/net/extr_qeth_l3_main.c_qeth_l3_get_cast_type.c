#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ protocol; scalar_t__ data; TYPE_2__* dev; } ;
struct TYPE_7__ {int link_type; } ;
struct qeth_card {TYPE_3__ info; } ;
struct TYPE_8__ {TYPE_1__* neighbour; } ;
struct TYPE_6__ {int /*<<< orphan*/  broadcast; } ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 int /*<<< orphan*/  QETH_ETH_MAC_V4 ; 
 int /*<<< orphan*/  QETH_ETH_MAC_V6 ; 
#define  QETH_LINK_TYPE_HSTR 129 
#define  QETH_LINK_TYPE_LANE_TR 128 
 int /*<<< orphan*/  QETH_TR_MAC_C ; 
 int /*<<< orphan*/  QETH_TR_MAC_NC ; 
 int RTN_ANYCAST ; 
 int RTN_BROADCAST ; 
 int RTN_MULTICAST ; 
 int RTN_UNSPEC ; 
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* skb_dst (struct sk_buff*) ; 
 int* skb_network_header (struct sk_buff*) ; 

int inline qeth_l3_get_cast_type(struct qeth_card *card, struct sk_buff *skb)
{
	int cast_type = RTN_UNSPEC;

	if (skb_dst(skb) && skb_dst(skb)->neighbour) {
		cast_type = skb_dst(skb)->neighbour->type;
		if ((cast_type == RTN_BROADCAST) ||
		    (cast_type == RTN_MULTICAST) ||
		    (cast_type == RTN_ANYCAST))
			return cast_type;
		else
			return RTN_UNSPEC;
	}
	/* try something else */
	if (skb->protocol == ETH_P_IPV6)
		return (skb_network_header(skb)[24] == 0xff) ?
				RTN_MULTICAST : 0;
	else if (skb->protocol == ETH_P_IP)
		return ((skb_network_header(skb)[16] & 0xf0) == 0xe0) ?
				RTN_MULTICAST : 0;
	/* ... */
	if (!memcmp(skb->data, skb->dev->broadcast, 6))
		return RTN_BROADCAST;
	else {
		u16 hdr_mac;

		hdr_mac = *((u16 *)skb->data);
		/* tr multicast? */
		switch (card->info.link_type) {
		case QETH_LINK_TYPE_HSTR:
		case QETH_LINK_TYPE_LANE_TR:
			if ((hdr_mac == QETH_TR_MAC_NC) ||
			    (hdr_mac == QETH_TR_MAC_C))
				return RTN_MULTICAST;
			break;
		/* eth or so multicast? */
		default:
		if ((hdr_mac == QETH_ETH_MAC_V4) ||
			    (hdr_mac == QETH_ETH_MAC_V6))
				return RTN_MULTICAST;
		}
	}
	return cast_type;
}