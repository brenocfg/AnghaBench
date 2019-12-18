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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int dummy; } ;
struct dn_scp {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DN_CI ; 
 scalar_t__ DN_NC ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void dn_returned_conn_init(struct sock *sk, struct sk_buff *skb)
{
	struct dn_scp *scp = DN_SK(sk);

	if (scp->state == DN_CI) {
		scp->state = DN_NC;
		sk->sk_state = TCP_CLOSE;
		if (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
	}

	kfree_skb(skb);
}