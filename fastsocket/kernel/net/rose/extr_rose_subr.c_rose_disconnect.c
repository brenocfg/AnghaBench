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
struct sock {int sk_err; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_state; } ;
struct rose_sock {int cause; int diagnostic; int /*<<< orphan*/  state; scalar_t__ lci; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROSE_STATE_0 ; 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  rose_clear_queues (struct sock*) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_idletimer (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void rose_disconnect(struct sock *sk, int reason, int cause, int diagnostic)
{
	struct rose_sock *rose = rose_sk(sk);

	rose_stop_timer(sk);
	rose_stop_idletimer(sk);

	rose_clear_queues(sk);

	rose->lci   = 0;
	rose->state = ROSE_STATE_0;

	if (cause != -1)
		rose->cause = cause;

	if (diagnostic != -1)
		rose->diagnostic = diagnostic;

	sk->sk_state     = TCP_CLOSE;
	sk->sk_err       = reason;
	sk->sk_shutdown |= SEND_SHUTDOWN;

	if (!sock_flag(sk, SOCK_DEAD)) {
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
	}
}