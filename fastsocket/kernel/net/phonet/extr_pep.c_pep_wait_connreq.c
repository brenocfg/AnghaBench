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
struct task_struct {int dummy; } ;
struct sock {scalar_t__ sk_state; TYPE_1__* sk_socket; } ;
struct pep_sock {int /*<<< orphan*/  ackq; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ TCP_LISTEN ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 long schedule_timeout (long) ; 
 scalar_t__ signal_pending (struct task_struct*) ; 
 int sock_intr_errno (long) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int pep_wait_connreq(struct sock *sk, int noblock)
{
	struct task_struct *tsk = current;
	struct pep_sock *pn = pep_sk(sk);
	long timeo = sock_rcvtimeo(sk, noblock);

	for (;;) {
		DEFINE_WAIT(wait);

		if (sk->sk_state != TCP_LISTEN)
			return -EINVAL;
		if (!hlist_empty(&pn->ackq))
			break;
		if (!timeo)
			return -EWOULDBLOCK;
		if (signal_pending(tsk))
			return sock_intr_errno(timeo);

		prepare_to_wait_exclusive(&sk->sk_socket->wait, &wait,
						TASK_INTERRUPTIBLE);
		release_sock(sk);
		timeo = schedule_timeout(timeo);
		lock_sock(sk);
		finish_wait(&sk->sk_socket->wait, &wait);
	}

	return 0;
}