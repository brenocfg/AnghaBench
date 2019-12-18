#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vfs_context_t ;
typedef  TYPE_2__* proc_t ;
struct TYPE_7__ {int p_lflag; int /*<<< orphan*/ * p_fd; } ;
struct TYPE_6__ {int /*<<< orphan*/ * vc_thread; } ;

/* Variables and functions */
 int P_LVFORK ; 
 TYPE_2__* current_proc () ; 
 scalar_t__ get_bsdthreadtask_info (int /*<<< orphan*/ *) ; 

proc_t
vfs_context_proc(vfs_context_t ctx)
{
	proc_t	proc = NULL;

	if (ctx != NULL && ctx->vc_thread != NULL)
		proc = (proc_t)get_bsdthreadtask_info(ctx->vc_thread);
	if (proc != NULL && (proc->p_fd == NULL || (proc->p_lflag & P_LVFORK)))
		proc = NULL;

	return(proc == NULL ? current_proc() : proc);
}