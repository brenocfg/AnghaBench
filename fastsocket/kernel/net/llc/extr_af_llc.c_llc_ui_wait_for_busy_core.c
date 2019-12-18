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
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_sleep; } ;
struct llc_sock {int /*<<< orphan*/  p_flag; int /*<<< orphan*/  remote_busy_flag; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_data_accept_state (int /*<<< orphan*/ ) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ sk_wait_event (struct sock*,long*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int llc_ui_wait_for_busy_core(struct sock *sk, long timeout)
{
	DEFINE_WAIT(wait);
	struct llc_sock *llc = llc_sk(sk);
	int rc;

	while (1) {
		prepare_to_wait(sk->sk_sleep, &wait, TASK_INTERRUPTIBLE);
		rc = 0;
		if (sk_wait_event(sk, &timeout,
				  (sk->sk_shutdown & RCV_SHUTDOWN) ||
				  (!llc_data_accept_state(llc->state) &&
				   !llc->remote_busy_flag &&
				   !llc->p_flag)))
			break;
		rc = -ERESTARTSYS;
		if (signal_pending(current))
			break;
		rc = -EAGAIN;
		if (!timeout)
			break;
	}
	finish_wait(sk->sk_sleep, &wait);
	return rc;
}