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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/ * function; } ;
struct sock {TYPE_1__ sk_timer; } ;
struct nr_sock {int /*<<< orphan*/  idletimer; int /*<<< orphan*/  t4timer; int /*<<< orphan*/  t2timer; int /*<<< orphan*/  t1timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  nr_heartbeat_expiry ; 
 int /*<<< orphan*/  nr_idletimer_expiry ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_t1timer_expiry ; 
 int /*<<< orphan*/  nr_t2timer_expiry ; 
 int /*<<< orphan*/  nr_t4timer_expiry ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void nr_init_timers(struct sock *sk)
{
	struct nr_sock *nr = nr_sk(sk);

	setup_timer(&nr->t1timer, nr_t1timer_expiry, (unsigned long)sk);
	setup_timer(&nr->t2timer, nr_t2timer_expiry, (unsigned long)sk);
	setup_timer(&nr->t4timer, nr_t4timer_expiry, (unsigned long)sk);
	setup_timer(&nr->idletimer, nr_idletimer_expiry, (unsigned long)sk);

	/* initialized by sock_init_data */
	sk->sk_timer.data     = (unsigned long)sk;
	sk->sk_timer.function = &nr_heartbeat_expiry;
}