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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ when; } ;
struct TYPE_3__ {scalar_t__ icsk_rto; } ;

/* Variables and functions */
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 scalar_t__ tcp_time_stamp ; 

__attribute__((used)) static inline int tcp_skb_timedout(struct sock *sk, struct sk_buff *skb)
{
	return (tcp_time_stamp - TCP_SKB_CB(skb)->when > inet_csk(sk)->icsk_rto);
}