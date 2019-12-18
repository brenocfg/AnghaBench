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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ TCP_CLOSE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ sk_wait_event (struct sock*,long*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int llc_ui_wait_for_disc(struct sock *sk, long timeout)
{
	DEFINE_WAIT(wait);
	int rc = 0;

	while (1) {
		prepare_to_wait(sk->sk_sleep, &wait, TASK_INTERRUPTIBLE);
		if (sk_wait_event(sk, &timeout, sk->sk_state == TCP_CLOSE))
			break;
		rc = -ERESTARTSYS;
		if (signal_pending(current))
			break;
		rc = -EAGAIN;
		if (!timeout)
			break;
		rc = 0;
	}
	finish_wait(sk->sk_sleep, &wait);
	return rc;
}