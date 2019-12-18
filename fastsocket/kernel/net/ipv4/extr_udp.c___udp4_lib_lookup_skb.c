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
struct udp_table {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sock* __udp4_lib_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udp_table*) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 struct sock* skb_steal_sock (struct sk_buff*) ; 
 scalar_t__ unlikely (struct sock*) ; 

__attribute__((used)) static inline struct sock *__udp4_lib_lookup_skb(struct sk_buff *skb,
						 __be16 sport, __be16 dport,
						 struct udp_table *udptable)
{
	struct sock *sk;
	const struct iphdr *iph = ip_hdr(skb);

	if (unlikely(sk = skb_steal_sock(skb)))
		return sk;
	else
		return __udp4_lib_lookup(dev_net(skb_dst(skb)->dev), iph->saddr, sport,
					 iph->daddr, dport, inet_iif(skb),
					 udptable);
}