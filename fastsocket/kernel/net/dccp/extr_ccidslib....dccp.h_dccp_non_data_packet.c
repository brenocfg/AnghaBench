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
struct sk_buff {int dummy; } ;
typedef  scalar_t__ __u8 ;
struct TYPE_2__ {scalar_t__ dccpd_type; } ;

/* Variables and functions */
 scalar_t__ const DCCP_PKT_ACK ; 
 scalar_t__ const DCCP_PKT_CLOSE ; 
 scalar_t__ const DCCP_PKT_CLOSEREQ ; 
 scalar_t__ const DCCP_PKT_RESET ; 
 scalar_t__ const DCCP_PKT_SYNC ; 
 scalar_t__ const DCCP_PKT_SYNCACK ; 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff const*) ; 

__attribute__((used)) static inline int dccp_non_data_packet(const struct sk_buff *skb)
{
	const __u8 type = DCCP_SKB_CB(skb)->dccpd_type;

	return type == DCCP_PKT_ACK	 ||
	       type == DCCP_PKT_CLOSE	 ||
	       type == DCCP_PKT_CLOSEREQ ||
	       type == DCCP_PKT_RESET	 ||
	       type == DCCP_PKT_SYNC	 ||
	       type == DCCP_PKT_SYNCACK;
}