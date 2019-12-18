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
struct sock {scalar_t__ sk_sleep; TYPE_1__* sk_socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int POLLOUT ; 
 int POLLWRBAND ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  SOCK_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  sock_writeable (struct sock*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (scalar_t__,int) ; 

__attribute__((used)) static void macvtap_sock_write_space(struct sock *sk)
{
	if (!sock_writeable(sk) ||
	    !test_and_clear_bit(SOCK_ASYNC_NOSPACE, &sk->sk_socket->flags))
		return;

	if (sk->sk_sleep && waitqueue_active(sk->sk_sleep))
		wake_up_interruptible_poll(sk->sk_sleep, POLLOUT | POLLWRNORM | POLLWRBAND);
}