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
struct sock {scalar_t__ sk_state; } ;
struct TYPE_4__ {int /*<<< orphan*/ * icsk_af_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hash ) (struct sock*) ;} ;

/* Variables and functions */
 scalar_t__ TCP_CLOSE ; 
 int /*<<< orphan*/  __inet6_hash (struct sock*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_mapped ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 TYPE_1__ tcp_prot ; 

__attribute__((used)) static void tcp_v6_hash(struct sock *sk)
{
	if (sk->sk_state != TCP_CLOSE) {
		if (inet_csk(sk)->icsk_af_ops == &ipv6_mapped) {
			tcp_prot.hash(sk);
			return;
		}
		local_bh_disable();
		__inet6_hash(sk);
		local_bh_enable();
	}
}