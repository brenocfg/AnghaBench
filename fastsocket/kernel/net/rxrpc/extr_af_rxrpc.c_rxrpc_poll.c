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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_sleep; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 scalar_t__ rxrpc_writable (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_poll_wait (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int rxrpc_poll(struct file *file, struct socket *sock,
			       poll_table *wait)
{
	unsigned int mask;
	struct sock *sk = sock->sk;

	sock_poll_wait(file, sk->sk_sleep, wait);
	mask = 0;

	/* the socket is readable if there are any messages waiting on the Rx
	 * queue */
	if (!skb_queue_empty(&sk->sk_receive_queue))
		mask |= POLLIN | POLLRDNORM;

	/* the socket is writable if there is space to add new data to the
	 * socket; there is no guarantee that any particular call in progress
	 * on the socket may have space in the Tx ACK window */
	if (rxrpc_writable(sk))
		mask |= POLLOUT | POLLWRNORM;

	return mask;
}