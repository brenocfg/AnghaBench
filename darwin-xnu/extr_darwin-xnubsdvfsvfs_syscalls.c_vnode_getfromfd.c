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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct fileproc {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  NULLVP ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_getfvp (int /*<<< orphan*/ ,int,struct fileproc**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int vnode_getwithref (int /*<<< orphan*/ ) ; 

int
vnode_getfromfd(vfs_context_t ctx, int fd, vnode_t *vpp)
{
	int error;
	vnode_t vp;
	struct fileproc *fp;
	proc_t p = vfs_context_proc(ctx);

	*vpp =  NULLVP;

	error = fp_getfvp(p, fd, &fp, &vp);
	if (error)
		return (error);

	error = vnode_getwithref(vp);
	if (error) {
		(void)fp_drop(p, fd, fp, 0);
		return (error);
	}

	(void)fp_drop(p, fd, fp, 0);
	*vpp = vp;
	return (error);
}