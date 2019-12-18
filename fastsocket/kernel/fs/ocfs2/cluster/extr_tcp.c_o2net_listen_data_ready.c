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
struct sock {void (* sk_user_data ) (struct sock*,int) ;void (* sk_data_ready ) (struct sock*,int) ;scalar_t__ sk_state; int /*<<< orphan*/  sk_callback_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_TCP ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  o2net_listen_work ; 
 int /*<<< orphan*/  o2net_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2net_listen_data_ready(struct sock *sk, int bytes)
{
	void (*ready)(struct sock *sk, int bytes);

	read_lock(&sk->sk_callback_lock);
	ready = sk->sk_user_data;
	if (ready == NULL) { /* check for teardown race */
		ready = sk->sk_data_ready;
		goto out;
	}

	/* ->sk_data_ready is also called for a newly established child socket
	 * before it has been accepted and the acceptor has set up their
	 * data_ready.. we only want to queue listen work for our listening
	 * socket */
	if (sk->sk_state == TCP_LISTEN) {
		mlog(ML_TCP, "bytes: %d\n", bytes);
		queue_work(o2net_wq, &o2net_listen_work);
	}

out:
	read_unlock(&sk->sk_callback_lock);
	ready(sk, bytes);
}