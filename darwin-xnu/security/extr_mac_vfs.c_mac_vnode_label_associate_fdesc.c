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
struct vnode {int /*<<< orphan*/  v_label; } ;
struct socket {int /*<<< orphan*/  so_label; } ;
struct proc {int dummy; } ;
struct pipe {int /*<<< orphan*/  pipe_label; } ;
struct mount {int /*<<< orphan*/  mnt_mntlabel; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
struct fdescnode {int fd_fd; } ;
typedef  int /*<<< orphan*/  socket_t ;
struct TYPE_2__ {int /*<<< orphan*/ * fg_label; scalar_t__ fg_data; } ;

/* Variables and functions */
#define  DTYPE_ATALK 136 
#define  DTYPE_FSEVENTS 135 
#define  DTYPE_KQUEUE 134 
#define  DTYPE_NETPOLICY 133 
#define  DTYPE_PIPE 132 
#define  DTYPE_PSXSEM 131 
#define  DTYPE_PSXSHM 130 
#define  DTYPE_SOCKET 129 
#define  DTYPE_VNODE 128 
 int EBADF ; 
 int EINVAL ; 
 int FILEGLOB_DTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_lookup (struct proc*,int,struct fileproc**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psem_label_associate (struct fileproc*,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pshm_label_associate (struct fileproc*,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 struct proc* vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_label_associate_file ; 
 int /*<<< orphan*/  vnode_label_associate_pipe ; 
 int /*<<< orphan*/  vnode_label_associate_socket ; 
 int /*<<< orphan*/  vnode_label_copy ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

int
mac_vnode_label_associate_fdesc(struct mount *mp, struct fdescnode *fnp,
    struct vnode *vp, vfs_context_t ctx)
{
	struct fileproc *fp;
#if CONFIG_MACF_SOCKET_SUBSET
	struct socket *so;
#endif
	struct pipe *cpipe;
	struct vnode *fvp;
	struct proc *p;
	int error;

	error = 0;

	/*
	 * If no backing file, let the policy choose which label to use.
	 */
	if (fnp->fd_fd == -1) {
		MAC_PERFORM(vnode_label_associate_file, vfs_context_ucred(ctx),
		    mp, mp->mnt_mntlabel, NULL, NULL, vp, vp->v_label);
		return (0);
	}

	p = vfs_context_proc(ctx);
	error = fp_lookup(p, fnp->fd_fd, &fp, 0);
	if (error)
		return (error);

	if (fp->f_fglob == NULL) {
		error = EBADF;
		goto out;
	}

	switch (FILEGLOB_DTYPE(fp->f_fglob)) {
	case DTYPE_VNODE:
		fvp = (struct vnode *)fp->f_fglob->fg_data;
		if ((error = vnode_getwithref(fvp)))
			goto out;
		MAC_PERFORM(vnode_label_copy, fvp->v_label, vp->v_label);
		(void)vnode_put(fvp);
		break;
#if CONFIG_MACF_SOCKET_SUBSET
	case DTYPE_SOCKET:
		so = (struct socket *)fp->f_fglob->fg_data;
		socket_lock(so, 1);
		MAC_PERFORM(vnode_label_associate_socket,
			    vfs_context_ucred(ctx), (socket_t)so, so->so_label,
		    vp, vp->v_label);
		socket_unlock(so, 1);
		break;
#endif
	case DTYPE_PSXSHM:
		pshm_label_associate(fp, vp, ctx);
		break;
	case DTYPE_PSXSEM:
		psem_label_associate(fp, vp, ctx);
		break;
	case DTYPE_PIPE:
		cpipe = (struct pipe *)fp->f_fglob->fg_data;
		/* kern/sys_pipe.c:pipe_select() suggests this test. */
		if (cpipe == (struct pipe *)-1) {
			error = EINVAL;
			goto out;
		}
		PIPE_LOCK(cpipe);
		MAC_PERFORM(vnode_label_associate_pipe, vfs_context_ucred(ctx),
		    cpipe, cpipe->pipe_label, vp, vp->v_label);
		PIPE_UNLOCK(cpipe);
		break;
	case DTYPE_KQUEUE:
	case DTYPE_FSEVENTS:
	case DTYPE_ATALK:
	case DTYPE_NETPOLICY:
	default:
		MAC_PERFORM(vnode_label_associate_file, vfs_context_ucred(ctx),
		    mp, mp->mnt_mntlabel, fp->f_fglob, fp->f_fglob->fg_label,
		    vp, vp->v_label);
		break;
	}
out:
	fp_drop(p, fnp->fd_fd, fp, 0);
	return (error);
}