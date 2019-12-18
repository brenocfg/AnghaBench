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
struct x25_sock {int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/ * function; } ;
struct sock {TYPE_1__ sk_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  x25_heartbeat_expiry ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_timer_expiry ; 

void x25_init_timers(struct sock *sk)
{
	struct x25_sock *x25 = x25_sk(sk);

	setup_timer(&x25->timer, x25_timer_expiry, (unsigned long)sk);

	/* initialized by sock_init_data */
	sk->sk_timer.data     = (unsigned long)sk;
	sk->sk_timer.function = &x25_heartbeat_expiry;
}