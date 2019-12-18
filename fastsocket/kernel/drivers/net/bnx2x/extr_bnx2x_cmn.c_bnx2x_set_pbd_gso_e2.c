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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ nexthdr; } ;
struct TYPE_3__ {int gso_size; } ;

/* Variables and functions */
 int ETH_TX_PARSE_BD_E2_IPV6_WITH_EXT_HDR ; 
 int ETH_TX_PARSE_BD_E2_LSO_MSS ; 
 int ETH_TX_PARSE_BD_E2_LSO_MSS_SHIFT ; 
 scalar_t__ NEXTHDR_IPV6 ; 
 int XMIT_GSO_V6 ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void bnx2x_set_pbd_gso_e2(struct sk_buff *skb, u32 *parsing_data,
				 u32 xmit_type)
{
	*parsing_data |= (skb_shinfo(skb)->gso_size <<
			      ETH_TX_PARSE_BD_E2_LSO_MSS_SHIFT) &
			      ETH_TX_PARSE_BD_E2_LSO_MSS;
	if ((xmit_type & XMIT_GSO_V6) &&
	    (ipv6_hdr(skb)->nexthdr == NEXTHDR_IPV6))
		*parsing_data |= ETH_TX_PARSE_BD_E2_IPV6_WITH_EXT_HDR;
}