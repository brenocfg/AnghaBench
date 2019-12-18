#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_13__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
struct vnode_attr {scalar_t__ va_uid; } ;
struct TYPE_23__ {int cn_flags; int /*<<< orphan*/  cn_nameptr; int /*<<< orphan*/  cn_nameiop; } ;
struct nameidata {TYPE_13__ ni_cnd; TYPE_2__* ni_vp; TYPE_2__* ni_dvp; int /*<<< orphan*/  ni_dirp; int /*<<< orphan*/  ni_op; } ;
struct TYPE_26__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_3__ fse_info ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
struct TYPE_25__ {scalar_t__ v_type; int v_parent; TYPE_1__* v_mount; } ;
struct TYPE_24__ {int /*<<< orphan*/  mnt_kern_flag; } ;

/* Variables and functions */
 int AT_SYMLINK_FOLLOW ; 
 int AUDITVNPATH1 ; 
 int AUDITVNPATH2 ; 
 int CN_NBMOUNTLOOK ; 
 int /*<<< orphan*/  CREATE ; 
 int EACCES ; 
 int EEXIST ; 
 int ENOMEM ; 
 int EPERM ; 
 int EXDEV ; 
 int FOLLOW ; 
 int /*<<< orphan*/  FSE_ARG_DONE ; 
 int /*<<< orphan*/  FSE_ARG_FINFO ; 
 int /*<<< orphan*/  FSE_ARG_STRING ; 
 int /*<<< orphan*/  FSE_ARG_VNODE ; 
 int /*<<< orphan*/  FSE_CREATE_FILE ; 
 int /*<<< orphan*/  FSE_STAT_CHANGED ; 
 int /*<<< orphan*/  FSE_TRUNCATED_PATH ; 
 int /*<<< orphan*/  GET_PATH (char*) ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_FILEOP_LINK ; 
 int /*<<< orphan*/  KAUTH_VNODE_ADD_FILE ; 
 int /*<<< orphan*/  KAUTH_VNODE_LINKTARGET ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  LOOKUP ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MNTK_DIR_HARDLINKS ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NOFOLLOW ; 
 TYPE_2__* NULLVP ; 
 int /*<<< orphan*/  OP_LINK ; 
 int /*<<< orphan*/  OP_LOOKUP ; 
 int /*<<< orphan*/  RELEASE_PATH (char*) ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VDIR ; 
 int VNOP_LINK (TYPE_2__*,TYPE_2__*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_fsevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 scalar_t__ get_fse_info (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_authorize_fileop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t) ; 
 int kauth_authorize_fileop_has_listeners () ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int mac_vnode_check_link (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_13__*) ; 
 int /*<<< orphan*/  mac_vnode_notify_link (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_13__*) ; 
 int nameiat (struct nameidata*,int) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int need_fsevent (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int safe_getpath (TYPE_2__*,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 scalar_t__ vn_getpath (TYPE_2__*,char*,int*) ; 
 int vnode_authorize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_getattr (TYPE_2__*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_mount (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_2__*) ; 

__attribute__((used)) static int
linkat_internal(vfs_context_t ctx, int fd1, user_addr_t path, int fd2,
    user_addr_t link, int flag, enum uio_seg segflg)
{
	vnode_t	vp, dvp, lvp;
	struct nameidata nd;
	int follow;
	int error;
#if CONFIG_FSE
	fse_info finfo;
#endif
	int need_event, has_listeners;
	char *target_path = NULL;
	int truncated=0;

	vp = dvp = lvp = NULLVP;

	/* look up the object we are linking to */
	follow = (flag & AT_SYMLINK_FOLLOW) ? FOLLOW : NOFOLLOW;
	NDINIT(&nd, LOOKUP, OP_LOOKUP, AUDITVNPATH1 | follow,
	    segflg, path, ctx);

	error = nameiat(&nd, fd1);
	if (error)
		return (error);
	vp = nd.ni_vp;

	nameidone(&nd);

	/*
	 * Normally, linking to directories is not supported.
	 * However, some file systems may have limited support.
	 */
	if (vp->v_type == VDIR) {
		if (!ISSET(vp->v_mount->mnt_kern_flag, MNTK_DIR_HARDLINKS)) {
			error = EPERM;   /* POSIX */
			goto out;
		}

		/* Linking to a directory requires ownership. */
		if (!kauth_cred_issuser(vfs_context_ucred(ctx))) {
			struct vnode_attr dva;

			VATTR_INIT(&dva);
			VATTR_WANTED(&dva, va_uid);
			if (vnode_getattr(vp, &dva, ctx) != 0 ||
			    !VATTR_IS_SUPPORTED(&dva, va_uid) ||
			    (dva.va_uid != kauth_cred_getuid(vfs_context_ucred(ctx)))) {
				error = EACCES;
				goto out;
			}
		}
	}

	/* lookup the target node */
#if CONFIG_TRIGGERS
	nd.ni_op = OP_LINK;
#endif
	nd.ni_cnd.cn_nameiop = CREATE;
	nd.ni_cnd.cn_flags = LOCKPARENT | AUDITVNPATH2 | CN_NBMOUNTLOOK;
	nd.ni_dirp = link;
	error = nameiat(&nd, fd2);
	if (error != 0)
		goto out;
	dvp = nd.ni_dvp;
	lvp = nd.ni_vp;

#if CONFIG_MACF
	if ((error = mac_vnode_check_link(ctx, dvp, vp, &nd.ni_cnd)) != 0)
		goto out2;
#endif

  	/* or to anything that kauth doesn't want us to (eg. immutable items) */
  	if ((error = vnode_authorize(vp, NULL, KAUTH_VNODE_LINKTARGET, ctx)) != 0)
 		goto out2;

	/* target node must not exist */
	if (lvp != NULLVP) {
		error = EEXIST;
		goto out2;
	}
  	/* cannot link across mountpoints */
  	if (vnode_mount(vp) != vnode_mount(dvp)) {
  		error = EXDEV;
  		goto out2;
  	}

  	/* authorize creation of the target note */
  	if ((error = vnode_authorize(dvp, NULL, KAUTH_VNODE_ADD_FILE, ctx)) != 0)
  		goto out2;

	/* and finally make the link */
	error = VNOP_LINK(vp, dvp, &nd.ni_cnd, ctx);
	if (error)
		goto out2;

#if CONFIG_MACF
	(void)mac_vnode_notify_link(ctx, vp, dvp, &nd.ni_cnd);
#endif

#if CONFIG_FSE
	need_event = need_fsevent(FSE_CREATE_FILE, dvp);
#else
	need_event = 0;
#endif
	has_listeners = kauth_authorize_fileop_has_listeners();

	if (need_event || has_listeners) {
		char *link_to_path = NULL;
		int len, link_name_len;

		/* build the path to the new link file */
		GET_PATH(target_path);
		if (target_path == NULL) {
			error = ENOMEM;
			goto out2;
		}

		len = safe_getpath(dvp, nd.ni_cnd.cn_nameptr, target_path, MAXPATHLEN, &truncated);

		if (has_listeners) {
		        /* build the path to file we are linking to */
			GET_PATH(link_to_path);
			if (link_to_path == NULL) {
				error = ENOMEM;
				goto out2;
			}

			link_name_len = MAXPATHLEN;
			if (vn_getpath(vp, link_to_path, &link_name_len) == 0) {
				/*
				 * Call out to allow 3rd party notification of rename.
				 * Ignore result of kauth_authorize_fileop call.
				 */
				kauth_authorize_fileop(vfs_context_ucred(ctx), KAUTH_FILEOP_LINK,
						       (uintptr_t)link_to_path,
						       (uintptr_t)target_path);
			}
			if (link_to_path != NULL) {
				RELEASE_PATH(link_to_path);
			}
		}
#if CONFIG_FSE
		if (need_event) {
		        /* construct fsevent */
		        if (get_fse_info(vp, &finfo, ctx) == 0) {
				if (truncated) {
					finfo.mode |= FSE_TRUNCATED_PATH;
				}

			        // build the path to the destination of the link
			        add_fsevent(FSE_CREATE_FILE, ctx,
					    FSE_ARG_STRING, len, target_path,
					    FSE_ARG_FINFO, &finfo,
					    FSE_ARG_DONE);
			}
			if (vp->v_parent) {
			    add_fsevent(FSE_STAT_CHANGED, ctx,
				FSE_ARG_VNODE, vp->v_parent,
				FSE_ARG_DONE);
			}
		}
#endif
	}
out2:
	/*
	 * nameidone has to happen before we vnode_put(dvp)
	 * since it may need to release the fs_nodelock on the dvp
	 */
	nameidone(&nd);
	if (target_path != NULL) {
		RELEASE_PATH(target_path);
	}
out:
	if (lvp)
		vnode_put(lvp);
	if (dvp)
		vnode_put(dvp);
	vnode_put(vp);
	return (error);
}