#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vfs_context_t ;
struct TYPE_7__ {scalar_t__ p_ucred; } ;
struct TYPE_6__ {scalar_t__ vc_ucred; int /*<<< orphan*/ * vc_thread; } ;

/* Variables and functions */
 scalar_t__ NOCRED ; 
 TYPE_1__ kerncontext ; 
 TYPE_3__* kernproc ; 
 int /*<<< orphan*/ * proc_thread (TYPE_3__*) ; 

vfs_context_t
vfs_context_kernel(void)
{
	if (kerncontext.vc_ucred == NOCRED)
		kerncontext.vc_ucred = kernproc->p_ucred;
	if (kerncontext.vc_thread == NULL)
		kerncontext.vc_thread = proc_thread(kernproc);

	return(&kerncontext);
}