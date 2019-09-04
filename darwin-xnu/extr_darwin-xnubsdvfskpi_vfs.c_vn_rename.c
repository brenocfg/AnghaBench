#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vfs_rename_flags_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
struct vnode_attr {int dummy; } ;
struct vnode {TYPE_2__* v_mount; } ;
struct nameidata {int dummy; } ;
struct componentname {int /*<<< orphan*/  cn_flags; } ;
typedef  int errno_t ;
struct TYPE_4__ {TYPE_1__* mnt_vtable; } ;
struct TYPE_3__ {int vfc_vfsflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_SECLUDE_RENAME ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  FREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 struct vnode* NULLVP ; 
 int SF_RESTRICTED ; 
 int UF_DATAVAULT ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int) ; 
 int VFC_VFSVNOP_SECLUDE_RENAME ; 
 scalar_t__ VFS_RENAME_SECLUDE ; 
 int VNOP_COMPOUND_RENAME (struct vnode*,struct vnode**,struct componentname*,struct vnode_attr*,struct vnode*,struct vnode**,struct componentname*,struct vnode_attr*,scalar_t__,int /*<<< orphan*/ ) ; 
 int VNOP_RENAME (struct vnode*,struct vnode*,struct componentname*,struct vnode*,struct vnode*,struct componentname*,int /*<<< orphan*/ ) ; 
 int VNOP_RENAMEX (struct vnode*,struct vnode*,struct componentname*,struct vnode*,struct vnode*,struct componentname*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  va_flags ; 
 int vnode_compound_rename_available (struct vnode*) ; 
 int vnode_flags (struct vnode*,int*,int /*<<< orphan*/ ) ; 
 int vnode_setattr (struct vnode*,struct vnode_attr*,int /*<<< orphan*/ ) ; 

errno_t
vn_rename(struct vnode *fdvp, struct vnode **fvpp, struct componentname *fcnp, struct vnode_attr *fvap,
            struct vnode *tdvp, struct vnode **tvpp, struct componentname *tcnp, struct vnode_attr *tvap,
            vfs_rename_flags_t flags, vfs_context_t ctx)
{
	int _err;
	struct nameidata *fromnd = NULL;
	struct nameidata *tond = NULL;
#if CONFIG_APPLEDOUBLE
	vnode_t src_attr_vp = NULLVP;
	vnode_t dst_attr_vp = NULLVP;
	char smallname1[48];
	char smallname2[48];
	char *xfromname = NULL;
	char *xtoname = NULL;
#endif /* CONFIG_APPLEDOUBLE */
	int batched;
	uint32_t tdfflags;	// Target directory file flags

	batched = vnode_compound_rename_available(fdvp);

	if (!batched) {
		if (*fvpp == NULLVP) 
			panic("Not batched, and no fvp?");
	}

#if CONFIG_APPLEDOUBLE
	/* 
	 * We need to preflight any potential AppleDouble file for the source file
	 * before doing the rename operation, since we could potentially be doing
	 * this operation on a network filesystem, and would end up duplicating
	 * the work.  Also, save the source and destination names.  Skip it if the
	 * source has a "._" prefix.
	 */
	
	if (!NATIVE_XATTR(fdvp) &&
	    !(fcnp->cn_nameptr[0] == '.' && fcnp->cn_nameptr[1] == '_')) {
		size_t len;
		int error;

		/* Get source attribute file name. */
		len = fcnp->cn_namelen + 3;
		if (len > sizeof(smallname1)) {
			MALLOC(xfromname, char *, len, M_TEMP, M_WAITOK);
		} else {
			xfromname = &smallname1[0];
		}
		strlcpy(xfromname, "._", min(sizeof smallname1, len));
		strncat(xfromname, fcnp->cn_nameptr, fcnp->cn_namelen);
		xfromname[len-1] = '\0';

		/* Get destination attribute file name. */
		len = tcnp->cn_namelen + 3;
		if (len > sizeof(smallname2)) {
			MALLOC(xtoname, char *, len, M_TEMP, M_WAITOK);
		} else {
			xtoname = &smallname2[0];
		}
		strlcpy(xtoname, "._", min(sizeof smallname2, len));
		strncat(xtoname, tcnp->cn_nameptr, tcnp->cn_namelen);
		xtoname[len-1] = '\0';
	
		/* 
		 * Look up source attribute file, keep reference on it if exists.
		 * Note that we do the namei with the nameiop of RENAME, which is different than
		 * in the rename syscall. It's OK if the source file does not exist, since this
		 * is only for AppleDouble files.
		 */
		MALLOC(fromnd, struct nameidata *, sizeof (struct nameidata), M_TEMP, M_WAITOK);
		NDINIT(fromnd, RENAME, OP_RENAME, NOFOLLOW | USEDVP | CN_NBMOUNTLOOK,
				UIO_SYSSPACE, CAST_USER_ADDR_T(xfromname), ctx);
		fromnd->ni_dvp = fdvp;
		error = namei(fromnd);

		/*
		 * If there was an error looking up source attribute file,
		 * we'll behave as if it didn't exist.
		 */

		if (error == 0) {
			if (fromnd->ni_vp) {
				/* src_attr_vp indicates need to call vnode_put / nameidone later */
				src_attr_vp = fromnd->ni_vp;

				if (fromnd->ni_vp->v_type != VREG) {
					src_attr_vp = NULLVP;
					vnode_put(fromnd->ni_vp);
				}
			}
			/*
			 * Either we got an invalid vnode type (not a regular file) or the namei lookup
			 * suppressed ENOENT as a valid error since we're renaming. Either way, we don't
			 * have a vnode here, so we drop our namei buffer for the source attribute file
			 */
			if (src_attr_vp == NULLVP) {
				nameidone(fromnd);
			}
		}
	}
#endif /* CONFIG_APPLEDOUBLE */

	if (batched) {
		_err = VNOP_COMPOUND_RENAME(fdvp, fvpp, fcnp, fvap, tdvp, tvpp, tcnp, tvap, flags, ctx);
		if (_err != 0) {
			printf("VNOP_COMPOUND_RENAME() returned %d\n", _err);
		}
	} else {
		if (flags) {
			_err = VNOP_RENAMEX(fdvp, *fvpp, fcnp, tdvp, *tvpp, tcnp, flags, ctx);
			if (_err == ENOTSUP && flags == VFS_RENAME_SECLUDE) {
				// Legacy...
				if ((*fvpp)->v_mount->mnt_vtable->vfc_vfsflags & VFC_VFSVNOP_SECLUDE_RENAME) {
					fcnp->cn_flags |= CN_SECLUDE_RENAME;
					_err = VNOP_RENAME(fdvp, *fvpp, fcnp, tdvp, *tvpp, tcnp, ctx);
				}
			}
		} else
			_err = VNOP_RENAME(fdvp, *fvpp, fcnp, tdvp, *tvpp, tcnp, ctx);
	}

	/*
	 * If moved to a new directory that is restricted,
	 * set the restricted flag on the item moved.
	 */
	if (_err == 0) {
		_err = vnode_flags(tdvp, &tdfflags, ctx);
		if (_err == 0) {
			uint32_t inherit_flags = tdfflags & (UF_DATAVAULT | SF_RESTRICTED);
			if (inherit_flags) {
				uint32_t fflags;
				_err = vnode_flags(*fvpp, &fflags, ctx);
				if (_err == 0 && fflags != (fflags | inherit_flags)) {
					struct vnode_attr va;
					VATTR_INIT(&va);
					VATTR_SET(&va, va_flags, fflags | inherit_flags);
					_err = vnode_setattr(*fvpp, &va, ctx);
				}
			}
		}
	}

#if CONFIG_MACF
	if (_err == 0) {
		mac_vnode_notify_rename(ctx, *fvpp, tdvp, tcnp);
	}
#endif

#if CONFIG_APPLEDOUBLE
	/* 
	 * Rename any associated extended attribute file (._ AppleDouble file).
	 */
	if (_err == 0 && !NATIVE_XATTR(fdvp) && xfromname != NULL) {
		int error = 0;
	
		/*
		 * Get destination attribute file vnode.
		 * Note that tdvp already has an iocount reference. Make sure to check that we
		 * get a valid vnode from namei.
		 */
		MALLOC(tond, struct nameidata *, sizeof(struct nameidata), M_TEMP, M_WAITOK);
		NDINIT(tond, RENAME, OP_RENAME,
		       NOCACHE | NOFOLLOW | USEDVP | CN_NBMOUNTLOOK, UIO_SYSSPACE,
		       CAST_USER_ADDR_T(xtoname), ctx);
		tond->ni_dvp = tdvp;
		error = namei(tond);

		if (error) 
			goto ad_error;
		
		if (tond->ni_vp) {
			dst_attr_vp = tond->ni_vp;
		}
		
		if (src_attr_vp) {
			const char *old_name = src_attr_vp->v_name;
			vnode_t old_parent = src_attr_vp->v_parent;
	
			if (batched) {
				error = VNOP_COMPOUND_RENAME(fdvp, &src_attr_vp, &fromnd->ni_cnd, NULL,
						tdvp, &dst_attr_vp, &tond->ni_cnd, NULL,
						0, ctx);
			} else {
				error = VNOP_RENAME(fdvp, src_attr_vp, &fromnd->ni_cnd, 
						tdvp, dst_attr_vp, &tond->ni_cnd, ctx);
			}

			if (error == 0 && old_name == src_attr_vp->v_name &&
					old_parent == src_attr_vp->v_parent) {
				int update_flags = VNODE_UPDATE_NAME;
				
				if (fdvp != tdvp)
					update_flags |= VNODE_UPDATE_PARENT;
				
				if ((src_attr_vp->v_mount->mnt_vtable->vfc_vfsflags & VFC_VFSVNOP_NOUPDATEID_RENAME) == 0) {
					vnode_update_identity(src_attr_vp, tdvp,
						tond->ni_cnd.cn_nameptr,
						tond->ni_cnd.cn_namelen,
						tond->ni_cnd.cn_hash,
						update_flags);
				}
			}
			
			/* kevent notifications for moving resource files 
			 * _err is zero if we're here, so no need to notify directories, code
			 * below will do that.  only need to post the rename on the source and
			 * possibly a delete on the dest
			 */
			post_event_if_success(src_attr_vp, error, NOTE_RENAME);
			if (dst_attr_vp) {
				post_event_if_success(dst_attr_vp, error, NOTE_DELETE);	
			}

		} else if (dst_attr_vp) {
			/*
			 * Just delete destination attribute file vnode if it exists, since
			 * we didn't have a source attribute file.
			 * Note that tdvp already has an iocount reference.
			 */

			struct vnop_remove_args args;
			
			args.a_desc    = &vnop_remove_desc;
			args.a_dvp     = tdvp;
			args.a_vp      = dst_attr_vp;
			args.a_cnp     = &tond->ni_cnd;
			args.a_context = ctx;

			if (error == 0) {
				error = (*tdvp->v_op[vnop_remove_desc.vdesc_offset])(&args);

				if (error == 0)
					vnode_setneedinactive(dst_attr_vp);
			}
			
			/* kevent notification for deleting the destination's attribute file
			 * if it existed.  Only need to post the delete on the destination, since
			 * the code below will handle the directories. 
			 */
			post_event_if_success(dst_attr_vp, error, NOTE_DELETE);	
		}
	}
ad_error:
	if (src_attr_vp) {
		vnode_put(src_attr_vp);
		nameidone(fromnd);
	}
	if (dst_attr_vp) {
		vnode_put(dst_attr_vp);
		nameidone(tond);
	}
	if (xfromname && xfromname != &smallname1[0]) {
		FREE(xfromname, M_TEMP);
	}
	if (xtoname && xtoname != &smallname2[0]) {
		FREE(xtoname, M_TEMP);
	}
#endif /* CONFIG_APPLEDOUBLE */
	if (fromnd) {
		FREE(fromnd, M_TEMP);
	}
	if (tond) {
		FREE(tond, M_TEMP);
	}
	return _err;
}