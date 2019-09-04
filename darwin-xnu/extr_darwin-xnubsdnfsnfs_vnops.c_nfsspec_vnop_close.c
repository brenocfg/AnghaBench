#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
struct vnop_close_args {int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_vp; } ;
struct vnode_attr {int /*<<< orphan*/  va_modify_time; int /*<<< orphan*/  va_access_time; } ;
typedef  TYPE_1__* nfsnode_t ;
typedef  int /*<<< orphan*/  mount_t ;
struct TYPE_5__ {int n_flag; int /*<<< orphan*/  n_mtim; int /*<<< orphan*/  n_atim; } ;

/* Variables and functions */
 int NACC ; 
 int NCHG ; 
 int NUPD ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VOCALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnop_close_args*) ; 
 int /*<<< orphan*/  VOFFSET (int /*<<< orphan*/ ) ; 
 TYPE_1__* VTONFS (int /*<<< orphan*/ ) ; 
 int nfs_node_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  spec_vnodeop_p ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  va_modify_time ; 
 int /*<<< orphan*/  vfs_isrdonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_isinuse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_setattr (int /*<<< orphan*/ ,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnop_close ; 

int
nfsspec_vnop_close(
	struct vnop_close_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		int a_fflag;
		vfs_context_t a_context;
	} */ *ap)
{
	vnode_t vp = ap->a_vp;
	nfsnode_t np = VTONFS(vp);
	struct vnode_attr vattr;
	mount_t mp;
	int error;

	if ((error = nfs_node_lock(np)))
		return (error);
	if (np->n_flag & (NACC | NUPD)) {
		np->n_flag |= NCHG;
		if (!vnode_isinuse(vp, 0) && (mp = vnode_mount(vp)) && !vfs_isrdonly(mp)) {
			VATTR_INIT(&vattr);
			if (np->n_flag & NACC) {
				vattr.va_access_time = np->n_atim;
				VATTR_SET_ACTIVE(&vattr, va_access_time);
			}
			if (np->n_flag & NUPD) {
				vattr.va_modify_time = np->n_mtim;
				VATTR_SET_ACTIVE(&vattr, va_modify_time);
			}
			nfs_node_unlock(np);
			vnode_setattr(vp, &vattr, ap->a_context);
		} else {
			nfs_node_unlock(np);
		}
	} else {
		nfs_node_unlock(np);
	}
	return (VOCALL(spec_vnodeop_p, VOFFSET(vnop_close), ap));
}