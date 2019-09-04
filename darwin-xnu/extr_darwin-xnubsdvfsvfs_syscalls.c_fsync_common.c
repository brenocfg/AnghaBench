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
struct fsync_args {int /*<<< orphan*/  fd; } ;
struct fileproc {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_VNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int VNOP_FSYNC (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  file_drop (int /*<<< orphan*/ ) ; 
 int fp_getfvp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fileproc**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vnode_getwithref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnpath ; 

__attribute__((used)) static int
fsync_common(proc_t p, struct fsync_args *uap, int flags)
{
	vnode_t vp;
	struct fileproc *fp;
	vfs_context_t ctx = vfs_context_current();
	int error;

	AUDIT_ARG(fd, uap->fd);

	if ( (error = fp_getfvp(p, uap->fd, &fp, &vp)) )
		return (error);
	if ( (error = vnode_getwithref(vp)) ) {
		file_drop(uap->fd);
		return(error);
	}

	AUDIT_ARG(vnpath, vp, ARG_VNODE1);

	error = VNOP_FSYNC(vp, flags, ctx);

#if NAMEDRSRCFORK
	/* Sync resource fork shadow file if necessary. */
	if ((error == 0) &&
	    (vp->v_flag & VISNAMEDSTREAM) &&
	    (vp->v_parent != NULLVP) &&
	    vnode_isshadow(vp) &&
	    (fp->f_flags & FP_WRITTEN)) {
		(void) vnode_flushnamedstream(vp->v_parent, vp, ctx);
	}
#endif

	(void)vnode_put(vp);
	file_drop(uap->fd);
	return (error);
}