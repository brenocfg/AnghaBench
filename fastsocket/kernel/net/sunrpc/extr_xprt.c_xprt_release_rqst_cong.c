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
struct rpc_task {int /*<<< orphan*/  tk_rqstp; int /*<<< orphan*/  tk_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xprt_put_cong (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xprt_release_rqst_cong(struct rpc_task *task)
{
	__xprt_put_cong(task->tk_xprt, task->tk_rqstp);
}