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
struct sock {scalar_t__ sk_err; } ;
struct TYPE_2__ {struct sock* sk; scalar_t__ dead; } ;
struct sctp_association {scalar_t__ state; int /*<<< orphan*/  wait; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EPIPE ; 
 int /*<<< orphan*/  SCTP_DEBUG_PRINTK (char*,struct sctp_association*,long,size_t) ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_PENDING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  sctp_association_hold (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_association_put (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  sctp_release_sock (struct sock*) ; 
 size_t sctp_wspace (struct sctp_association*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int sctp_wait_for_sndbuf(struct sctp_association *asoc, long *timeo_p,
				size_t msg_len)
{
	struct sock *sk = asoc->base.sk;
	int err = 0;
	long current_timeo = *timeo_p;
	DEFINE_WAIT(wait);

	SCTP_DEBUG_PRINTK("wait_for_sndbuf: asoc=%p, timeo=%ld, msg_len=%zu\n",
			  asoc, (long)(*timeo_p), msg_len);

	/* Increment the association's refcnt.  */
	sctp_association_hold(asoc);

	/* Wait on the association specific sndbuf space. */
	for (;;) {
		prepare_to_wait_exclusive(&asoc->wait, &wait,
					  TASK_INTERRUPTIBLE);
		if (!*timeo_p)
			goto do_nonblock;
		if (sk->sk_err || asoc->state >= SCTP_STATE_SHUTDOWN_PENDING ||
		    asoc->base.dead)
			goto do_error;
		if (signal_pending(current))
			goto do_interrupted;
		if (msg_len <= sctp_wspace(asoc))
			break;

		/* Let another process have a go.  Since we are going
		 * to sleep anyway.
		 */
		sctp_release_sock(sk);
		current_timeo = schedule_timeout(current_timeo);
		BUG_ON(sk != asoc->base.sk);
		sctp_lock_sock(sk);

		*timeo_p = current_timeo;
	}

out:
	finish_wait(&asoc->wait, &wait);

	/* Release the association's refcnt.  */
	sctp_association_put(asoc);

	return err;

do_error:
	err = -EPIPE;
	goto out;

do_interrupted:
	err = sock_intr_errno(*timeo_p);
	goto out;

do_nonblock:
	err = -EAGAIN;
	goto out;
}