#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
struct user64_stat64 {int dummy; } ;
struct user64_stat {int dummy; } ;
struct user32_stat64 {int dummy; } ;
struct user32_stat {int dummy; } ;
struct stat64 {long long* st_qspare; int st_nlink; int /*<<< orphan*/  st_mode; scalar_t__ st_lspare; } ;
struct stat {long long* st_qspare; int st_nlink; int /*<<< orphan*/  st_mode; scalar_t__ st_lspare; } ;
struct TYPE_8__ {int /*<<< orphan*/  cn_flags; } ;
struct nameidata {TYPE_2__* ni_vp; TYPE_1__ ni_cnd; } ;
typedef  scalar_t__ kauth_filesec_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
typedef  scalar_t__ caddr_t ;
struct TYPE_9__ {scalar_t__ v_parent; } ;

/* Variables and functions */
 int AT_SYMLINK_NOFOLLOW ; 
 int AUDITVNPATH1 ; 
 int /*<<< orphan*/  CN_ALLOWRSRCFORK ; 
 int EFAULT ; 
 int FOLLOW ; 
 scalar_t__ IS_64BIT_PROCESS (int /*<<< orphan*/ ) ; 
 size_t KAUTH_FILESEC_COPYSIZE (scalar_t__) ; 
 scalar_t__ KAUTH_FILESEC_NONE ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NOFOLLOW ; 
 scalar_t__ NULLVP ; 
 int /*<<< orphan*/  OP_GETATTR ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int copyout (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 size_t fusize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_filesec_free (scalar_t__) ; 
 int /*<<< orphan*/  munge_user32_stat (struct stat*,struct user32_stat*) ; 
 int /*<<< orphan*/  munge_user32_stat64 (struct stat64*,struct user32_stat64*) ; 
 int /*<<< orphan*/  munge_user64_stat (struct stat*,struct user64_stat*) ; 
 int /*<<< orphan*/  munge_user64_stat64 (struct stat64*,struct user64_stat64*) ; 
 int nameiat (struct nameidata*,int) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 scalar_t__ susize (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int vn_stat (TYPE_2__*,void*,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isnamedstream (TYPE_2__*) ; 
 scalar_t__ vnode_isshadow (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_rele (TYPE_2__*) ; 

__attribute__((used)) static int
fstatat_internal(vfs_context_t ctx, user_addr_t path, user_addr_t ub,
    user_addr_t xsecurity, user_addr_t xsecurity_size, int isstat64,
    enum uio_seg segflg, int fd, int flag)
{
	struct nameidata nd;
	int follow;
	union {
		struct stat sb;
		struct stat64 sb64;
	} source = {};
	union {
		struct user64_stat user64_sb;
		struct user32_stat user32_sb;
		struct user64_stat64 user64_sb64;
		struct user32_stat64 user32_sb64;
	} dest = {};
	caddr_t sbp;
	int error, my_size;
	kauth_filesec_t fsec;
	size_t xsecurity_bufsize;
	void * statptr;

	follow = (flag & AT_SYMLINK_NOFOLLOW) ? NOFOLLOW : FOLLOW;
	NDINIT(&nd, LOOKUP, OP_GETATTR, follow | AUDITVNPATH1,
	    segflg, path, ctx);

#if NAMEDRSRCFORK
	int is_namedstream = 0;
	/* stat calls are allowed for resource forks. */
	nd.ni_cnd.cn_flags |= CN_ALLOWRSRCFORK;
#endif
	error = nameiat(&nd, fd);
	if (error)
		return (error);
	fsec = KAUTH_FILESEC_NONE;

	statptr = (void *)&source;

#if NAMEDRSRCFORK
	/* Grab reference on the shadow stream file vnode to
	 * force an inactive on release which will mark it
	 * for recycle.
	 */
	if (vnode_isnamedstream(nd.ni_vp) &&
	    (nd.ni_vp->v_parent != NULLVP) &&
	    vnode_isshadow(nd.ni_vp)) {
		is_namedstream = 1;
		vnode_ref(nd.ni_vp);
	}
#endif

	error = vn_stat(nd.ni_vp, statptr, (xsecurity != USER_ADDR_NULL ? &fsec : NULL), isstat64, ctx);

#if NAMEDRSRCFORK
	if (is_namedstream) {
		vnode_rele(nd.ni_vp);
	}
#endif
	vnode_put(nd.ni_vp);
	nameidone(&nd);

	if (error)
		return (error);
	/* Zap spare fields */
	if (isstat64 != 0) {
		source.sb64.st_lspare = 0;
		source.sb64.st_qspare[0] = 0LL;
		source.sb64.st_qspare[1] = 0LL;
		if (IS_64BIT_PROCESS(vfs_context_proc(ctx))) {
			munge_user64_stat64(&source.sb64, &dest.user64_sb64);
			my_size = sizeof(dest.user64_sb64);
			sbp = (caddr_t)&dest.user64_sb64;
		} else {
			munge_user32_stat64(&source.sb64, &dest.user32_sb64);
			my_size = sizeof(dest.user32_sb64);
			sbp = (caddr_t)&dest.user32_sb64;
		}
		/*
		 * Check if we raced (post lookup) against the last unlink of a file.
		 */
		if ((source.sb64.st_nlink == 0) && S_ISREG(source.sb64.st_mode)) {
			source.sb64.st_nlink = 1;
		}
	} else {
		source.sb.st_lspare = 0;
		source.sb.st_qspare[0] = 0LL;
		source.sb.st_qspare[1] = 0LL;
		if (IS_64BIT_PROCESS(vfs_context_proc(ctx))) {
			munge_user64_stat(&source.sb, &dest.user64_sb);
			my_size = sizeof(dest.user64_sb);
			sbp = (caddr_t)&dest.user64_sb;
		} else {
			munge_user32_stat(&source.sb, &dest.user32_sb);
			my_size = sizeof(dest.user32_sb);
			sbp = (caddr_t)&dest.user32_sb;
		}

		/*
		 * Check if we raced (post lookup) against the last unlink of a file.
		 */
		if ((source.sb.st_nlink == 0) && S_ISREG(source.sb.st_mode)) {
			source.sb.st_nlink = 1;
		}
	}
	if ((error = copyout(sbp, ub, my_size)) != 0)
		goto out;

	/* caller wants extended security information? */
	if (xsecurity != USER_ADDR_NULL) {

		/* did we get any? */
		if (fsec == KAUTH_FILESEC_NONE) {
			if (susize(xsecurity_size, 0) != 0) {
				error = EFAULT;
				goto out;
			}
		} else {
			/* find the user buffer size */
			xsecurity_bufsize = fusize(xsecurity_size);

			/* copy out the actual data size */
			if (susize(xsecurity_size, KAUTH_FILESEC_COPYSIZE(fsec)) != 0) {
				error = EFAULT;
				goto out;
			}

			/* if the caller supplied enough room, copy out to it */
			if (xsecurity_bufsize >= KAUTH_FILESEC_COPYSIZE(fsec))
				error = copyout(fsec, xsecurity, KAUTH_FILESEC_COPYSIZE(fsec));
		}
	}
out:
	if (fsec != KAUTH_FILESEC_NONE)
		kauth_filesec_free(fsec);
	return (error);
}