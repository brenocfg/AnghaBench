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
struct sock {int /*<<< orphan*/  sk_sleep; scalar_t__ sk_err; int /*<<< orphan*/  sk_write_pending; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_hc_tx_ccid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int EPIPE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int ccid_hc_tx_send_packet (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,int) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  schedule_timeout (unsigned long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int dccp_wait_for_ccid(struct sock *sk, struct sk_buff *skb, int delay)
{
	struct dccp_sock *dp = dccp_sk(sk);
	DEFINE_WAIT(wait);
	unsigned long jiffdelay;
	int rc;

	do {
		dccp_pr_debug("delayed send by %d msec\n", delay);
		jiffdelay = msecs_to_jiffies(delay);

		prepare_to_wait(sk->sk_sleep, &wait, TASK_INTERRUPTIBLE);

		sk->sk_write_pending++;
		release_sock(sk);
		schedule_timeout(jiffdelay);
		lock_sock(sk);
		sk->sk_write_pending--;

		if (sk->sk_err)
			goto do_error;
		if (signal_pending(current))
			goto do_interrupted;

		rc = ccid_hc_tx_send_packet(dp->dccps_hc_tx_ccid, sk, skb);
	} while ((delay = rc) > 0);
out:
	finish_wait(sk->sk_sleep, &wait);
	return rc;

do_error:
	rc = -EPIPE;
	goto out;
do_interrupted:
	rc = -EINTR;
	goto out;
}