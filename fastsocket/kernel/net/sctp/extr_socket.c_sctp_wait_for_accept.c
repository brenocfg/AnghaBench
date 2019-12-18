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
struct sock {int /*<<< orphan*/  sk_sleep; } ;
struct sctp_endpoint {int /*<<< orphan*/  asocs; } ;
struct TYPE_2__ {struct sctp_endpoint* ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  LISTENING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  sctp_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  sctp_release_sock (struct sock*) ; 
 TYPE_1__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sctp_sstate (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int sctp_wait_for_accept(struct sock *sk, long timeo)
{
	struct sctp_endpoint *ep;
	int err = 0;
	DEFINE_WAIT(wait);

	ep = sctp_sk(sk)->ep;


	for (;;) {
		prepare_to_wait_exclusive(sk->sk_sleep, &wait,
					  TASK_INTERRUPTIBLE);

		if (list_empty(&ep->asocs)) {
			sctp_release_sock(sk);
			timeo = schedule_timeout(timeo);
			sctp_lock_sock(sk);
		}

		err = -EINVAL;
		if (!sctp_sstate(sk, LISTENING))
			break;

		err = 0;
		if (!list_empty(&ep->asocs))
			break;

		err = sock_intr_errno(timeo);
		if (signal_pending(current))
			break;

		err = -EAGAIN;
		if (!timeo)
			break;
	}

	finish_wait(sk->sk_sleep, &wait);

	return err;
}