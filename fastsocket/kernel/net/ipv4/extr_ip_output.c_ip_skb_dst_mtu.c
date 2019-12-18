#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ sk; } ;
struct inet_sock {scalar_t__ pmtudisc; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int mtu; } ;

/* Variables and functions */
 scalar_t__ IP_PMTUDISC_PROBE ; 
 int dst_mtu (TYPE_2__*) ; 
 struct inet_sock* inet_sk (scalar_t__) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static inline int ip_skb_dst_mtu(struct sk_buff *skb)
{
	struct inet_sock *inet = skb->sk ? inet_sk(skb->sk) : NULL;

	return (inet && inet->pmtudisc == IP_PMTUDISC_PROBE) ?
	       skb_dst(skb)->dev->mtu : dst_mtu(skb_dst(skb));
}