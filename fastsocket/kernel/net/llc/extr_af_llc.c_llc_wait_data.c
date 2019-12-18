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
struct sock {int sk_shutdown; } ;

/* Variables and functions */
 int EAGAIN ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ sk_wait_data (struct sock*,long*) ; 
 int sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 

__attribute__((used)) static int llc_wait_data(struct sock *sk, long timeo)
{
	int rc;

	while (1) {
		/*
		 * POSIX 1003.1g mandates this order.
		 */
		rc = sock_error(sk);
		if (rc)
			break;
		rc = 0;
		if (sk->sk_shutdown & RCV_SHUTDOWN)
			break;
		rc = -EAGAIN;
		if (!timeo)
			break;
		rc = sock_intr_errno(timeo);
		if (signal_pending(current))
			break;
		rc = 0;
		if (sk_wait_data(sk, &timeo))
			break;
	}
	return rc;
}