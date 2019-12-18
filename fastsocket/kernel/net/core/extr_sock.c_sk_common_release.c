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
struct sock {TYPE_1__* sk_prot; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;int /*<<< orphan*/  (* destroy ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sk_refcnt_debug_release (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  xfrm_sk_free_policy (struct sock*) ; 

void sk_common_release(struct sock *sk)
{
	if (sk->sk_prot->destroy)
		sk->sk_prot->destroy(sk);

	/*
	 * Observation: when sock_common_release is called, processes have
	 * no access to socket. But net still has.
	 * Step one, detach it from networking:
	 *
	 * A. Remove from hash tables.
	 */

	sk->sk_prot->unhash(sk);

	/*
	 * In this point socket cannot receive new packets, but it is possible
	 * that some packets are in flight because some CPU runs receiver and
	 * did hash table lookup before we unhashed socket. They will achieve
	 * receive queue and will be purged by socket destructor.
	 *
	 * Also we still have packets pending on receive queue and probably,
	 * our own packets waiting in device queues. sock_destroy will drain
	 * receive queue, but transmitted packets will delay socket destruction
	 * until the last reference will be released.
	 */

	sock_orphan(sk);

	xfrm_sk_free_policy(sk);

	sk_refcnt_debug_release(sk);
	sock_put(sk);
}