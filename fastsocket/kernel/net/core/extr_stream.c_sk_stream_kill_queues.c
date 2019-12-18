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
struct sock {int sk_wmem_queued; int sk_forward_alloc; int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_error_queue; int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

void sk_stream_kill_queues(struct sock *sk)
{
	/* First the read buffer. */
	__skb_queue_purge(&sk->sk_receive_queue);

	/* Next, the error queue. */
	__skb_queue_purge(&sk->sk_error_queue);

	/* Next, the write queue. */
	WARN_ON(!skb_queue_empty(&sk->sk_write_queue));

	/* Account for returned memory. */
	sk_mem_reclaim(sk);

	WARN_ON(sk->sk_wmem_queued);
	WARN_ON(sk->sk_forward_alloc);

	/* It is _impossible_ for the backlog to contain anything
	 * when we get here.  All user references to this socket
	 * have gone away, only the net layer knows can touch it.
	 */
}