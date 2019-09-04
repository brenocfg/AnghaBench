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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  u_long ;
struct fileproc {TYPE_1__* f_ops; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int (* fo_ioctl ) (struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  proc_fdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 
 int stub1 (struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 

int
fo_ioctl(struct fileproc *fp, u_long com, caddr_t data, vfs_context_t ctx)
{
	int error;

	proc_fdunlock(vfs_context_proc(ctx));
	error = (*fp->f_ops->fo_ioctl)(fp, com, data, ctx);
	proc_fdlock(vfs_context_proc(ctx));
	return(error);
}