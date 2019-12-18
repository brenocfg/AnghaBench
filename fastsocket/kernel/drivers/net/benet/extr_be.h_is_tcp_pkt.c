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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int version; scalar_t__ protocol; } ;
struct TYPE_3__ {scalar_t__ nexthdr; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ NEXTHDR_TCP ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline u8 is_tcp_pkt(struct sk_buff *skb)
{
	u8 val = 0;

	if (ip_hdr(skb)->version == 4)
		val = (ip_hdr(skb)->protocol == IPPROTO_TCP);
	else if (ip_hdr(skb)->version == 6)
		val = (ipv6_hdr(skb)->nexthdr == NEXTHDR_TCP);

	return val;
}