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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_5__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_8__ {TYPE_2__ saddr; TYPE_1__ daddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 TYPE_4__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  secure_tcpv6_sequence_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static __u32 tcp_v6_init_sequence(struct sk_buff *skb)
{
	return secure_tcpv6_sequence_number(ipv6_hdr(skb)->daddr.s6_addr32,
					    ipv6_hdr(skb)->saddr.s6_addr32,
					    tcp_hdr(skb)->dest,
					    tcp_hdr(skb)->source);
}