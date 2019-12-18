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
struct sock {int sk_userlocks; TYPE_1__* sk_prot; scalar_t__ sk_bound_dev_if; int /*<<< orphan*/  sk_state; } ;
struct inet_sock {scalar_t__ sport; scalar_t__ dport; scalar_t__ daddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int SOCK_BINDADDR_LOCK ; 
 int SOCK_BINDPORT_LOCK ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  inet_reset_saddr (struct sock*) ; 
 int /*<<< orphan*/  inet_rps_save_rxhash (struct sock*,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int udp_disconnect(struct sock *sk, int flags)
{
	struct inet_sock *inet = inet_sk(sk);
	/*
	 *	1003.1g - break association.
	 */

	sk->sk_state = TCP_CLOSE;
	inet->daddr = 0;
	inet->dport = 0;
	inet_rps_save_rxhash(sk, 0);
	sk->sk_bound_dev_if = 0;
	if (!(sk->sk_userlocks & SOCK_BINDADDR_LOCK))
		inet_reset_saddr(sk);

	if (!(sk->sk_userlocks & SOCK_BINDPORT_LOCK)) {
		sk->sk_prot->unhash(sk);
		inet->sport = 0;
	}
	sk_dst_reset(sk);
	return 0;
}