#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  TYPE_2__* vfs_context_t ;
typedef  TYPE_3__* uthread_t ;
typedef  TYPE_4__* proc_t ;
struct TYPE_10__ {TYPE_1__* p_fd; } ;
struct TYPE_9__ {int /*<<< orphan*/  uu_cdir; } ;
struct TYPE_8__ {int /*<<< orphan*/ * vc_thread; } ;
struct TYPE_7__ {int /*<<< orphan*/  fd_cdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLVP ; 
 TYPE_3__* get_bsdthread_info (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bsdthreadtask_info (int /*<<< orphan*/ *) ; 

vnode_t
vfs_context_cwd(vfs_context_t ctx)
{
	vnode_t cwd = NULLVP;

	if(ctx != NULL && ctx->vc_thread != NULL) {
		uthread_t uth = get_bsdthread_info(ctx->vc_thread);
		proc_t proc;

		/*
		 * Get the cwd from the thread; if there isn't one, get it
		 * from the process, instead.
		 */
		if ((cwd = uth->uu_cdir) == NULLVP &&
		    (proc = (proc_t)get_bsdthreadtask_info(ctx->vc_thread)) != NULL &&
		    proc->p_fd != NULL)
			cwd = proc->p_fd->fd_cdir;
	}

	return(cwd);
}