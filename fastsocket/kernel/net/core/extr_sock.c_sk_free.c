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
struct sock {int /*<<< orphan*/  sk_wmem_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_free (struct sock*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 

void sk_free(struct sock *sk)
{
	/*
	 * We substract one from sk_wmem_alloc and can know if
	 * some packets are still in some tx queue.
	 * If not null, sock_wfree() will call __sk_free(sk) later
	 */
	if (atomic_dec_and_test(&sk->sk_wmem_alloc))
		__sk_free(sk);
		//FPRINTK("Release socket 0x%p[%u]\n", sk, atomic_read(&sk->sk_wmem_alloc));
}