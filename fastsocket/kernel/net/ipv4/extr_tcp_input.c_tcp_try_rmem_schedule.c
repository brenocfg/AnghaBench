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
struct sock {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_rmem_schedule (struct sock*,unsigned int) ; 
 int /*<<< orphan*/  tcp_prune_ofo_queue (struct sock*) ; 
 scalar_t__ tcp_prune_queue (struct sock*) ; 

__attribute__((used)) static inline int tcp_try_rmem_schedule(struct sock *sk, unsigned int size)
{
	if (atomic_read(&sk->sk_rmem_alloc) > sk->sk_rcvbuf ||
	    !sk_rmem_schedule(sk, size)) {

		if (tcp_prune_queue(sk) < 0)
			return -1;

		if (!sk_rmem_schedule(sk, size)) {
			if (!tcp_prune_ofo_queue(sk))
				return -1;

			if (!sk_rmem_schedule(sk, size))
				return -1;
		}
	}
	return 0;
}