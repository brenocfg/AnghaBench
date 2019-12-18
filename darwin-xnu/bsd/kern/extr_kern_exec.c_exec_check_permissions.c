#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_size_t ;
struct vnode_attr {int va_mode; scalar_t__ va_data_size; } ;
struct vnode {scalar_t__ v_writecount; TYPE_1__* v_mount; } ;
struct image_params {scalar_t__ ip_arch_size; int ip_flags; int /*<<< orphan*/  ip_vfs_context; scalar_t__ ip_arch_offset; struct vnode_attr* ip_vattr; struct vnode* ip_vp; } ;
typedef  TYPE_2__* proc_t ;
typedef  int /*<<< orphan*/  kauth_action_t ;
struct TYPE_5__ {int p_lflag; } ;
struct TYPE_4__ {int mnt_flag; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOEXEC ; 
 int ETXTBSY ; 
 int IMGPF_ALLOW_DATA_EXEC ; 
 int IMGPF_DISABLE_ASLR ; 
 int /*<<< orphan*/  KAUTH_VNODE_EXECUTE ; 
 int /*<<< orphan*/  KAUTH_VNODE_READ_DATA ; 
 int MNT_NOSUID ; 
 int P_LTRACED ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VSGID ; 
 int VSUID ; 
 int mac_vnode_check_exec (int /*<<< orphan*/ ,struct vnode*,struct image_params*) ; 
 int /*<<< orphan*/  panic (char*,struct vnode*) ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_fileid ; 
 int /*<<< orphan*/  va_fsid ; 
 int /*<<< orphan*/  va_fsid64 ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  vfs_authopaque (int /*<<< orphan*/ ) ; 
 TYPE_2__* vfs_context_proc (int /*<<< orphan*/ ) ; 
 int vnode_authorize (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnode_getattr (struct vnode*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_isreg (struct vnode*) ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

__attribute__((used)) static int
exec_check_permissions(struct image_params *imgp)
{
	struct vnode *vp = imgp->ip_vp;
	struct vnode_attr *vap = imgp->ip_vattr;
	proc_t p = vfs_context_proc(imgp->ip_vfs_context);
	int error;
	kauth_action_t action;

	/* Only allow execution of regular files */
	if (!vnode_isreg(vp))
		return (EACCES);
	
	/* Get the file attributes that we will be using here and elsewhere */
	VATTR_INIT(vap);
	VATTR_WANTED(vap, va_uid);
	VATTR_WANTED(vap, va_gid);
	VATTR_WANTED(vap, va_mode);
	VATTR_WANTED(vap, va_fsid);
	VATTR_WANTED(vap, va_fsid64);
	VATTR_WANTED(vap, va_fileid);
	VATTR_WANTED(vap, va_data_size);
	if ((error = vnode_getattr(vp, vap, imgp->ip_vfs_context)) != 0)
		return (error);

	/*
	 * Ensure that at least one execute bit is on - otherwise root
	 * will always succeed, and we don't want to happen unless the
	 * file really is executable.
	 */
	if (!vfs_authopaque(vnode_mount(vp)) && ((vap->va_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) == 0))
		return (EACCES);

	/* Disallow zero length files */
	if (vap->va_data_size == 0)
		return (ENOEXEC);

	imgp->ip_arch_offset = (user_size_t)0;
	imgp->ip_arch_size = vap->va_data_size;

	/* Disable setuid-ness for traced programs or if MNT_NOSUID */
	if ((vp->v_mount->mnt_flag & MNT_NOSUID) || (p->p_lflag & P_LTRACED))
		vap->va_mode &= ~(VSUID | VSGID);

	/*
	 * Disable _POSIX_SPAWN_ALLOW_DATA_EXEC and _POSIX_SPAWN_DISABLE_ASLR
	 * flags for setuid/setgid binaries.
	 */
	if (vap->va_mode & (VSUID | VSGID))
		imgp->ip_flags &= ~(IMGPF_ALLOW_DATA_EXEC | IMGPF_DISABLE_ASLR);

#if CONFIG_MACF
	error = mac_vnode_check_exec(imgp->ip_vfs_context, vp, imgp);
	if (error)
		return (error);
#endif

  	/* Check for execute permission */
 	action = KAUTH_VNODE_EXECUTE;
  	/* Traced images must also be readable */
 	if (p->p_lflag & P_LTRACED)
 		action |= KAUTH_VNODE_READ_DATA;
 	if ((error = vnode_authorize(vp, NULL, action, imgp->ip_vfs_context)) != 0)
		return (error);

#if 0
	/* Don't let it run if anyone had it open for writing */
	vnode_lock(vp);
	if (vp->v_writecount) {
		panic("going to return ETXTBSY %x", vp);
		vnode_unlock(vp);
		return (ETXTBSY);
	}
	vnode_unlock(vp);
#endif


	/* XXX May want to indicate to underlying FS that vnode is open */

	return (error);
}