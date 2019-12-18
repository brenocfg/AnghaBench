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
struct tcp_sock {scalar_t__ ecn_flags; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int TCPCB_FLAG_CWR ; 
 int TCPCB_FLAG_ECE ; 
 scalar_t__ TCP_ECN_OK ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 int sysctl_tcp_ecn ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static inline void TCP_ECN_send_syn(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);

	tp->ecn_flags = 0;
	if (sysctl_tcp_ecn == 1) {
		TCP_SKB_CB(skb)->flags |= TCPCB_FLAG_ECE | TCPCB_FLAG_CWR;
		tp->ecn_flags = TCP_ECN_OK;
	}
}