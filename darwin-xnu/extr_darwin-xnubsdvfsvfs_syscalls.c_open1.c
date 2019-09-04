#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  TYPE_1__* uthread_t ;
struct vnode_attr {int va_mode; } ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; } ;
struct nameidata {scalar_t__ ni_vp; } ;
struct flock {int /*<<< orphan*/  l_type; scalar_t__ l_len; scalar_t__ l_start; void* l_whence; } ;
struct fileproc {TYPE_13__* f_fglob; } ;
typedef  TYPE_2__* proc_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  fp_allocfn_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* fo_ioctl ) (struct fileproc*,int,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int p_flag; int /*<<< orphan*/  p_fd; } ;
struct TYPE_15__ {int uu_dupfd; } ;
struct TYPE_14__ {int fg_flag; int /*<<< orphan*/  fg_cred; TYPE_3__* fg_ops; int /*<<< orphan*/ * fg_vn_data; scalar_t__ fg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CLR (int,int) ; 
 scalar_t__ DTYPE_VNODE ; 
 int EINTR ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int EPERM ; 
 int ERESTART ; 
 int FENCRYPTED ; 
 int FFLAGS (int) ; 
 int FHASLOCK ; 
 scalar_t__ FILEGLOB_DTYPE (TYPE_13__*) ; 
 int FMASK ; 
 int FNONBLOCK ; 
 int FUNENCRYPTED ; 
 int FWRITE ; 
 int F_FLOCK ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int F_WAIT ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int O_ACCMODE ; 
 int O_CLOEXEC ; 
 int O_CLOFORK ; 
 int O_EVTONLY ; 
 int O_EXLOCK ; 
 int O_NOCTTY ; 
 int O_SHLOCK ; 
 int O_TRUNC ; 
 int P_CONTROLT ; 
 void* SEEK_SET ; 
 scalar_t__ TIOCSCTTY ; 
 int /*<<< orphan*/  UF_EXCLOSE ; 
 int /*<<< orphan*/  UF_FORKCLOSE ; 
 scalar_t__ VDIR ; 
 int VNOP_ADVLOCK (scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct flock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dupfdopen (int /*<<< orphan*/ ,int,int,int,int) ; 
 int falloc_withalloc (TYPE_2__*,struct fileproc**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * fdflags (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fflags ; 
 int /*<<< orphan*/ * fg_vn_data_alloc () ; 
 int /*<<< orphan*/  fp_drop (TYPE_2__*,int,struct fileproc*,int) ; 
 int /*<<< orphan*/  fp_free (TYPE_2__*,int,struct fileproc*) ; 
 TYPE_1__* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_2__*) ; 
 int /*<<< orphan*/  procfdtbl_releasefd (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fileproc*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct vfs_context* vfs_context_current () ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 TYPE_2__* vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_close (scalar_t__,int,struct vfs_context*) ; 
 int vn_open_auth (struct nameidata*,int*,struct vnode_attr*) ; 
 scalar_t__ vnode_isswap (scalar_t__) ; 
 scalar_t__ vnode_istty (scalar_t__) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 
 int vnode_setsize (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_vtype (scalar_t__) ; 
 TYPE_3__ vnops ; 

int
open1(vfs_context_t ctx, struct nameidata *ndp, int uflags,
    struct vnode_attr *vap, fp_allocfn_t fp_zalloc, void *cra,
    int32_t *retval)
{
	proc_t p = vfs_context_proc(ctx);
	uthread_t uu = get_bsdthread_info(vfs_context_thread(ctx));
	struct fileproc *fp;
	vnode_t vp;
	int flags, oflags;
	int type, indx, error;
	struct flock lf;
	struct vfs_context context;

	oflags = uflags;

	if ((oflags & O_ACCMODE) == O_ACCMODE)
		return(EINVAL);

	flags = FFLAGS(uflags);
	CLR(flags, FENCRYPTED);
	CLR(flags, FUNENCRYPTED);

	AUDIT_ARG(fflags, oflags);
	AUDIT_ARG(mode, vap->va_mode);

	if ((error = falloc_withalloc(p,
	    &fp, &indx, ctx, fp_zalloc, cra)) != 0) {
		return (error);
	}
	uu->uu_dupfd = -indx - 1;

	if ((error = vn_open_auth(ndp, &flags, vap))) {
		if ((error == ENODEV || error == ENXIO) && (uu->uu_dupfd >= 0)){	/* XXX from fdopen */
			if ((error = dupfdopen(p->p_fd, indx, uu->uu_dupfd, flags, error)) == 0) {
				fp_drop(p, indx, NULL, 0);
			        *retval = indx;
				return (0);
			}
		}
		if (error == ERESTART)
		        error = EINTR;
		fp_free(p, indx, fp);
		return (error);
	}
	uu->uu_dupfd = 0;
	vp = ndp->ni_vp;

	fp->f_fglob->fg_flag = flags & (FMASK | O_EVTONLY | FENCRYPTED | FUNENCRYPTED);
	fp->f_fglob->fg_ops = &vnops;
	fp->f_fglob->fg_data = (caddr_t)vp;

	if (flags & (O_EXLOCK | O_SHLOCK)) {
		lf.l_whence = SEEK_SET;
		lf.l_start = 0;
		lf.l_len = 0;
		if (flags & O_EXLOCK)
			lf.l_type = F_WRLCK;
		else
			lf.l_type = F_RDLCK;
		type = F_FLOCK;
		if ((flags & FNONBLOCK) == 0)
			type |= F_WAIT;
#if CONFIG_MACF
		error = mac_file_check_lock(vfs_context_ucred(ctx), fp->f_fglob,
		    F_SETLK, &lf);
		if (error)
			goto bad;
#endif
		if ((error = VNOP_ADVLOCK(vp, (caddr_t)fp->f_fglob, F_SETLK, &lf, type, ctx, NULL)))
			goto bad;
		fp->f_fglob->fg_flag |= FHASLOCK;
	}

#if DEVELOPMENT || DEBUG
	/*
	 * XXX VSWAP: Check for entitlements or special flag here
	 * so we can restrict access appropriately.
	 */
#else /* DEVELOPMENT || DEBUG */

	if (vnode_isswap(vp) && (flags & (FWRITE | O_TRUNC)) && (ctx != vfs_context_kernel())) {
		/* block attempt to write/truncate swapfile */
		error = EPERM;
		goto bad;
	}
#endif /* DEVELOPMENT || DEBUG */

	/* try to truncate by setting the size attribute */
	if ((flags & O_TRUNC) && ((error = vnode_setsize(vp, (off_t)0, 0, ctx)) != 0))
		goto bad;

	/*
	 * For directories we hold some additional information in the fd.
	 */
	if (vnode_vtype(vp) == VDIR) {
		fp->f_fglob->fg_vn_data = fg_vn_data_alloc();
	} else {
		fp->f_fglob->fg_vn_data = NULL;
	}

	vnode_put(vp);

	/*
	 * The first terminal open (without a O_NOCTTY) by a session leader
	 * results in it being set as the controlling terminal.
	 */
	if (vnode_istty(vp) && !(p->p_flag & P_CONTROLT) &&
	    !(flags & O_NOCTTY)) {
		int tmp = 0;

		(void)(*fp->f_fglob->fg_ops->fo_ioctl)(fp, (int)TIOCSCTTY,
		    (caddr_t)&tmp, ctx);
	}

	proc_fdlock(p);
	if (flags & O_CLOEXEC)
		*fdflags(p, indx) |= UF_EXCLOSE;
	if (flags & O_CLOFORK)
		*fdflags(p, indx) |= UF_FORKCLOSE;
	procfdtbl_releasefd(p, indx, NULL);

#if CONFIG_SECLUDED_MEMORY
	if (secluded_for_filecache &&
	    FILEGLOB_DTYPE(fp->f_fglob) == DTYPE_VNODE &&
	    vnode_vtype(vp) == VREG) {
		memory_object_control_t moc;

		moc = ubc_getobject(vp, UBC_FLAGS_NONE);

		if (moc == MEMORY_OBJECT_CONTROL_NULL) {
			/* nothing to do... */
		} else if (fp->f_fglob->fg_flag & FWRITE) {
			/* writable -> no longer  eligible for secluded pages */
			memory_object_mark_eligible_for_secluded(moc,
								 FALSE);
		} else if (secluded_for_filecache == 1) {
			char pathname[32] = { 0, };
			size_t copied;
			/* XXX FBDP: better way to detect /Applications/ ? */
			if (UIO_SEG_IS_USER_SPACE(ndp->ni_segflg)) {
				copyinstr(ndp->ni_dirp,
					  pathname,
					  sizeof (pathname),
					  &copied);
			} else {
				copystr(CAST_DOWN(void *, ndp->ni_dirp),
					pathname,
					sizeof (pathname),
					&copied);
			}
			pathname[sizeof (pathname) - 1] = '\0';
			if (strncmp(pathname,
				    "/Applications/",
				    strlen("/Applications/")) == 0 &&
			    strncmp(pathname,
				    "/Applications/Camera.app/",
				    strlen("/Applications/Camera.app/")) != 0) {
				/*
				 * not writable
				 * AND from "/Applications/"
				 * AND not from "/Applications/Camera.app/"
				 * ==> eligible for secluded
				 */
				memory_object_mark_eligible_for_secluded(moc,
									 TRUE);
			}
		} else if (secluded_for_filecache == 2) {
#if __arm64__
#define DYLD_SHARED_CACHE_NAME "dyld_shared_cache_arm64"
#elif __arm__
#define DYLD_SHARED_CACHE_NAME "dyld_shared_cache_armv7"
#else
/* not implemented... */
#endif
			if (!strncmp(vp->v_name,
				     DYLD_SHARED_CACHE_NAME,
				     strlen(DYLD_SHARED_CACHE_NAME)) ||
			    !strncmp(vp->v_name,
				     "dyld",
				     strlen(vp->v_name)) ||
			    !strncmp(vp->v_name,
				     "launchd",
				     strlen(vp->v_name)) ||
			    !strncmp(vp->v_name,
				     "Camera",
				     strlen(vp->v_name)) ||
			    !strncmp(vp->v_name,
				     "mediaserverd",
				     strlen(vp->v_name)) || 
			    !strncmp(vp->v_name,
				     "SpringBoard",
				     strlen(vp->v_name)) || 
			    !strncmp(vp->v_name,
				     "backboardd",
				     strlen(vp->v_name))) {
				/*
				 * This file matters when launching Camera:
				 * do not store its contents in the secluded
				 * pool that will be drained on Camera launch.
				 */
				memory_object_mark_eligible_for_secluded(moc,
									 FALSE);
			}
		}
	}
#endif /* CONFIG_SECLUDED_MEMORY */

	fp_drop(p, indx, fp, 1);
	proc_fdunlock(p);

	*retval = indx;

	return (0);
bad:
	context = *vfs_context_current();
	context.vc_ucred = fp->f_fglob->fg_cred;

    	if ((fp->f_fglob->fg_flag & FHASLOCK) &&
	    (FILEGLOB_DTYPE(fp->f_fglob) == DTYPE_VNODE)) {
		lf.l_whence = SEEK_SET;
        	lf.l_start = 0;
        	lf.l_len = 0;
        	lf.l_type = F_UNLCK;

        	(void)VNOP_ADVLOCK(
        		vp, (caddr_t)fp->f_fglob, F_UNLCK, &lf, F_FLOCK, ctx, NULL);
	}

	vn_close(vp, fp->f_fglob->fg_flag, &context);
	vnode_put(vp);
	fp_free(p, indx, fp);

	return (error);
}