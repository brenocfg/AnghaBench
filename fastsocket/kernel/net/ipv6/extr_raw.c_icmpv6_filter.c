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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int* data; } ;
struct raw6_sock {TYPE_1__ filter; } ;
struct icmp6hdr {int icmp6_type; } ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ pskb_may_pull (struct sk_buff*,int) ; 
 struct raw6_sock* raw6_sk (struct sock*) ; 

__attribute__((used)) static __inline__ int icmpv6_filter(struct sock *sk, struct sk_buff *skb)
{
	struct icmp6hdr *icmph;
	struct raw6_sock *rp = raw6_sk(sk);

	if (pskb_may_pull(skb, sizeof(struct icmp6hdr))) {
		__u32 *data = &rp->filter.data[0];
		int bit_nr;

		icmph = (struct icmp6hdr *) skb->data;
		bit_nr = icmph->icmp6_type;

		return (data[bit_nr >> 5] & (1 << (bit_nr & 31))) != 0;
	}
	return 0;
}