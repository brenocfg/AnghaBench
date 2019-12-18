#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct icmphdr {int dummy; } ;
typedef  int __u32 ;
struct TYPE_6__ {int type; } ;
struct TYPE_4__ {int data; } ;
struct TYPE_5__ {TYPE_1__ filter; } ;

/* Variables and functions */
 TYPE_3__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 TYPE_2__* raw_sk (struct sock*) ; 

__attribute__((used)) static __inline__ int icmp_filter(struct sock *sk, struct sk_buff *skb)
{
	int type;

	if (!pskb_may_pull(skb, sizeof(struct icmphdr)))
		return 1;

	type = icmp_hdr(skb)->type;
	if (type < 32) {
		__u32 data = raw_sk(sk)->filter.data;

		return ((1 << type) & data) != 0;
	}

	/* Do not block unknown ICMP types */
	return 0;
}