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
struct sock {int /*<<< orphan*/ * sk_send_head; } ;
struct TYPE_4__ {int /*<<< orphan*/  icsk_retransmits; TYPE_1__* icsk_af_ops; } ;
struct TYPE_3__ {scalar_t__ (* rebuild_header ) (struct sock*) ;} ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int dccp_transmit_skb (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  skb_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct sock*) ; 

int dccp_retransmit_skb(struct sock *sk)
{
	WARN_ON(sk->sk_send_head == NULL);

	if (inet_csk(sk)->icsk_af_ops->rebuild_header(sk) != 0)
		return -EHOSTUNREACH; /* Routing failure or similar. */

	/* this count is used to distinguish original and retransmitted skb */
	inet_csk(sk)->icsk_retransmits++;

	return dccp_transmit_skb(sk, skb_clone(sk->sk_send_head, GFP_ATOMIC));
}