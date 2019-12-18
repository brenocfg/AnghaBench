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
struct rpc_xprt {struct rpc_task* snd_task; } ;
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xprt_lock_write_next_cong (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_clear_locked (struct rpc_xprt*) ; 

void xprt_release_xprt_cong(struct rpc_xprt *xprt, struct rpc_task *task)
{
	if (xprt->snd_task == task) {
		xprt_clear_locked(xprt);
		__xprt_lock_write_next_cong(xprt);
	}
}