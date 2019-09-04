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
typedef  struct vnode* vnode_t ;
typedef  scalar_t__ uint32_t ;
struct vnode {scalar_t__ v_id; } ;
struct fileproc {scalar_t__ f_type; scalar_t__ f_data; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int EINVAL ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int) ; 
 int fp_lookup (int /*<<< orphan*/ ,int,struct fileproc**,int) ; 
 int /*<<< orphan*/  proc_fdlock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 

int
file_vnode_withvid(int fd, struct vnode **vpp, uint32_t * vidp)
{
	proc_t p = current_proc();
	struct fileproc *fp;
	vnode_t vp;
	int error;

	proc_fdlock_spin(p);
	if ( (error = fp_lookup(p, fd, &fp, 1)) ) {
		proc_fdunlock(p);
		return(error);
	}
	if (fp->f_type != DTYPE_VNODE) {
		fp_drop(p, fd, fp,1);
		proc_fdunlock(p);
		return(EINVAL);
	}
	vp = (struct vnode *)fp->f_data;
	if (vpp != NULL)
		*vpp = vp;

	if ((vidp != NULL) && (vp != NULLVP))
		*vidp = (uint32_t)vp->v_id;

	proc_fdunlock(p);

	return(0);
}