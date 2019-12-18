#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int /*<<< orphan*/  destructor; struct sock* sk; } ;

/* Variables and functions */
 scalar_t__ TCP_TIME_WAIT ; 
 int /*<<< orphan*/  inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_tproxy_destructor ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 

void
nf_tproxy_assign_sock(struct sk_buff *skb, struct sock *sk)
{
	/* assigning tw sockets complicates things; most
	 * skb->sk->X checks would have to test sk->sk_state first */
	if (sk->sk_state == TCP_TIME_WAIT) {
		inet_twsk_put(inet_twsk(sk));
		return;
	}

	skb_orphan(skb);
	skb->sk = sk;
	skb->destructor = nf_tproxy_destructor;
}