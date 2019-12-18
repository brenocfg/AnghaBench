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
struct sock {scalar_t__ sk_state; } ;
struct TYPE_2__ {int /*<<< orphan*/ * icsk_af_ops; } ;

/* Variables and functions */
 scalar_t__ DCCP_CLOSED ; 
 int /*<<< orphan*/  __inet6_hash (struct sock*) ; 
 int /*<<< orphan*/  dccp_ipv6_mapped ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_hash (struct sock*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

__attribute__((used)) static void dccp_v6_hash(struct sock *sk)
{
	if (sk->sk_state != DCCP_CLOSED) {
		if (inet_csk(sk)->icsk_af_ops == &dccp_ipv6_mapped) {
			inet_hash(sk);
			return;
		}
		local_bh_disable();
		__inet6_hash(sk);
		local_bh_enable();
	}
}