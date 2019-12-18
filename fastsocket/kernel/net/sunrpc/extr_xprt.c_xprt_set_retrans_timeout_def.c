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
struct rpc_task {TYPE_1__* tk_rqstp; int /*<<< orphan*/  tk_timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  rq_timeout; } ;

/* Variables and functions */

void xprt_set_retrans_timeout_def(struct rpc_task *task)
{
	task->tk_timeout = task->tk_rqstp->rq_timeout;
}