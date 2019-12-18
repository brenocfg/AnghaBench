#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vfs_context_t ;
typedef  int /*<<< orphan*/ * task_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_3__ {int /*<<< orphan*/ * vc_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/ * get_threadtask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_special_port (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

kern_return_t
vfs_context_set_special_port(vfs_context_t ctx, int which, ipc_port_t port)
{
	task_t			task = NULL;

	if (ctx != NULL && ctx->vc_thread != NULL)
		task = get_threadtask(ctx->vc_thread);

	return task_set_special_port(task, which, port);
}