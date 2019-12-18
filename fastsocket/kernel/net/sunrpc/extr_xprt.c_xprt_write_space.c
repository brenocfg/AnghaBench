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
struct rpc_xprt {int /*<<< orphan*/  transport_lock; scalar_t__ snd_task; int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct rpc_xprt*) ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void xprt_write_space(struct rpc_xprt *xprt)
{
	spin_lock_bh(&xprt->transport_lock);
	if (xprt->snd_task) {
		dprintk("RPC:       write space: waking waiting task on "
				"xprt %p\n", xprt);
		rpc_wake_up_queued_task(&xprt->pending, xprt->snd_task);
	}
	spin_unlock_bh(&xprt->transport_lock);
}