#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uid_t ;
struct vnode_attr {int va_active; int va_uid; int va_gid; int va_data_size; int va_total_size; int va_modify_time; int /*<<< orphan*/  va_guuid; int /*<<< orphan*/  va_uuuid; int /*<<< orphan*/ * va_acl; } ;
typedef  TYPE_4__* kauth_filesec_t ;
typedef  int /*<<< orphan*/ * kauth_acl_t ;
typedef  int gid_t ;
struct TYPE_16__ {int* val; } ;
struct TYPE_17__ {int f_iosize; scalar_t__ f_bsize; TYPE_1__ f_fsid; } ;
struct TYPE_20__ {int mnt_flag; int mnt_fsowner; int mnt_fsgroup; TYPE_2__ mnt_vfsstat; } ;
struct TYPE_15__ {scalar_t__ acl_entrycount; } ;
struct TYPE_19__ {int fsec_owner; int fsec_group; TYPE_11__ fsec_acl; } ;
struct TYPE_18__ {int v_type; TYPE_9__* v_mount; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KAUTH_ACL_COPYSIZE (TYPE_11__*) ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,int) ; 
 scalar_t__ KAUTH_FILESEC_NOACL ; 
 int KAUTH_GID_NONE ; 
 int KAUTH_UID_NONE ; 
 int MNT_IGNORE_OWNERSHIP ; 
 int /*<<< orphan*/  VATTR_CLEAR_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_CLEAR_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VATTR_NOT_RETURNED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_RETURN (struct vnode_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VATTR_SET_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS_KERNEL_EVENT ; 
 int VNODE_ATTR_ALL ; 
 int VNOP_GETATTR (TYPE_3__*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ XATTR_VNODE_SUPPORTED (TYPE_3__*) ; 
 int /*<<< orphan*/  bcopy (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kauth_acl_alloc (scalar_t__) ; 
 int /*<<< orphan*/  kauth_acl_free (int /*<<< orphan*/ *) ; 
 int kauth_cred_getgid (int /*<<< orphan*/ ) ; 
 int kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int kauth_cred_guid2gid (int /*<<< orphan*/ *,int*) ; 
 int kauth_cred_guid2uid (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  kauth_filesec_free (TYPE_4__*) ; 
 int /*<<< orphan*/  kauth_guid_equal (int /*<<< orphan*/ *,int*) ; 
 int kauth_null_guid ; 
 int roundup (int,scalar_t__) ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_change_time ; 
 int /*<<< orphan*/  va_data_alloc ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_filerev ; 
 int /*<<< orphan*/  va_flags ; 
 int /*<<< orphan*/  va_fsid ; 
 int /*<<< orphan*/  va_gen ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_guuid ; 
 int /*<<< orphan*/  va_iosize ; 
 int /*<<< orphan*/  va_modify_time ; 
 int /*<<< orphan*/  va_total_alloc ; 
 int /*<<< orphan*/  va_total_size ; 
 int /*<<< orphan*/  va_type ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  va_uuuid ; 
 scalar_t__ vfs_context_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_extendedsecurity (int /*<<< orphan*/ ) ; 
 int vfs_update_vfsstat (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnode_get_filesec (TYPE_3__*,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (TYPE_3__*) ; 

int
vnode_getattr(vnode_t vp, struct vnode_attr *vap, vfs_context_t ctx)
{
	kauth_filesec_t fsec;
	kauth_acl_t facl;
	int	error;
	uid_t	nuid;
	gid_t	ngid;

	/*
	 * Reject attempts to fetch unknown attributes.
	 */
	if (vap->va_active & ~VNODE_ATTR_ALL)
		return (EINVAL);

	/* don't ask for extended security data if the filesystem doesn't support it */
	if (!vfs_extendedsecurity(vnode_mount(vp))) {
		VATTR_CLEAR_ACTIVE(vap, va_acl);
		VATTR_CLEAR_ACTIVE(vap, va_uuuid);
		VATTR_CLEAR_ACTIVE(vap, va_guuid);
	}

	/*
	 * If the caller wants size values we might have to synthesise, give the
	 * filesystem the opportunity to supply better intermediate results.
	 */
	if (VATTR_IS_ACTIVE(vap, va_data_alloc) ||
	    VATTR_IS_ACTIVE(vap, va_total_size) ||
	    VATTR_IS_ACTIVE(vap, va_total_alloc)) {
		VATTR_SET_ACTIVE(vap, va_data_size);
		VATTR_SET_ACTIVE(vap, va_data_alloc);
		VATTR_SET_ACTIVE(vap, va_total_size);
		VATTR_SET_ACTIVE(vap, va_total_alloc);
	}
	
	error = VNOP_GETATTR(vp, vap, ctx);
	if (error) {
		KAUTH_DEBUG("ERROR - returning %d", error);
		goto out;
	}

	/*
	 * If extended security data was requested but not returned, try the fallback
	 * path.
	 */
	if (VATTR_NOT_RETURNED(vap, va_acl) || VATTR_NOT_RETURNED(vap, va_uuuid) || VATTR_NOT_RETURNED(vap, va_guuid)) {
		fsec = NULL;

		if (XATTR_VNODE_SUPPORTED(vp)) {
			/* try to get the filesec */
			if ((error = vnode_get_filesec(vp, &fsec, ctx)) != 0)
				goto out;
		}
		/* if no filesec, no attributes */
		if (fsec == NULL) {
			VATTR_RETURN(vap, va_acl, NULL);
			VATTR_RETURN(vap, va_uuuid, kauth_null_guid);
			VATTR_RETURN(vap, va_guuid, kauth_null_guid);
		} else {

			/* looks good, try to return what we were asked for */
			VATTR_RETURN(vap, va_uuuid, fsec->fsec_owner);
			VATTR_RETURN(vap, va_guuid, fsec->fsec_group);

			/* only return the ACL if we were actually asked for it */
			if (VATTR_IS_ACTIVE(vap, va_acl)) {
				if (fsec->fsec_acl.acl_entrycount == KAUTH_FILESEC_NOACL) {
					VATTR_RETURN(vap, va_acl, NULL);
				} else {
					facl = kauth_acl_alloc(fsec->fsec_acl.acl_entrycount);
					if (facl == NULL) {
						kauth_filesec_free(fsec);
						error = ENOMEM;
						goto out;
					}
					bcopy(&fsec->fsec_acl, facl, KAUTH_ACL_COPYSIZE(&fsec->fsec_acl));
					VATTR_RETURN(vap, va_acl, facl);
				}
			}
			kauth_filesec_free(fsec);
		}
	}
	/*
	 * If someone gave us an unsolicited filesec, toss it.  We promise that
	 * we're OK with a filesystem giving us anything back, but our callers
	 * only expect what they asked for.
	 */
	if (VATTR_IS_SUPPORTED(vap, va_acl) && !VATTR_IS_ACTIVE(vap, va_acl)) {
		if (vap->va_acl != NULL)
			kauth_acl_free(vap->va_acl);
		VATTR_CLEAR_SUPPORTED(vap, va_acl);
	}

#if 0	/* enable when we have a filesystem only supporting UUIDs */
	/*
	 * Handle the case where we need a UID/GID, but only have extended
	 * security information.
	 */
	if (VATTR_NOT_RETURNED(vap, va_uid) &&
	    VATTR_IS_SUPPORTED(vap, va_uuuid) &&
	    !kauth_guid_equal(&vap->va_uuuid, &kauth_null_guid)) {
		if ((error = kauth_cred_guid2uid(&vap->va_uuuid, &nuid)) == 0)
			VATTR_RETURN(vap, va_uid, nuid);
	}
	if (VATTR_NOT_RETURNED(vap, va_gid) &&
	    VATTR_IS_SUPPORTED(vap, va_guuid) &&
	    !kauth_guid_equal(&vap->va_guuid, &kauth_null_guid)) {
		if ((error = kauth_cred_guid2gid(&vap->va_guuid, &ngid)) == 0)
			VATTR_RETURN(vap, va_gid, ngid);
	}
#endif
	
	/*
	 * Handle uid/gid == 99 and MNT_IGNORE_OWNERSHIP here.
	 */
	if (VATTR_IS_ACTIVE(vap, va_uid)) {
		if (vfs_context_issuser(ctx) && VATTR_IS_SUPPORTED(vap, va_uid)) {
			nuid = vap->va_uid;
		} else if (vp->v_mount->mnt_flag & MNT_IGNORE_OWNERSHIP) {
			nuid = vp->v_mount->mnt_fsowner;
			if (nuid == KAUTH_UID_NONE)
				nuid = 99;
		} else if (VATTR_IS_SUPPORTED(vap, va_uid)) {
			nuid = vap->va_uid;
		} else {
			/* this will always be something sensible */
			nuid = vp->v_mount->mnt_fsowner;
		}
		if ((nuid == 99) && !vfs_context_issuser(ctx))
			nuid = kauth_cred_getuid(vfs_context_ucred(ctx));
		VATTR_RETURN(vap, va_uid, nuid);
	}
	if (VATTR_IS_ACTIVE(vap, va_gid)) {
		if (vfs_context_issuser(ctx) && VATTR_IS_SUPPORTED(vap, va_gid)) {
			ngid = vap->va_gid;
		} else if (vp->v_mount->mnt_flag & MNT_IGNORE_OWNERSHIP) {
			ngid = vp->v_mount->mnt_fsgroup;
			if (ngid == KAUTH_GID_NONE)
				ngid = 99;
		} else if (VATTR_IS_SUPPORTED(vap, va_gid)) {
			ngid = vap->va_gid;
		} else {
			/* this will always be something sensible */
			ngid = vp->v_mount->mnt_fsgroup;
		}
		if ((ngid == 99) && !vfs_context_issuser(ctx))
			ngid = kauth_cred_getgid(vfs_context_ucred(ctx));
		VATTR_RETURN(vap, va_gid, ngid);
	}

	/*
	 * Synthesise some values that can be reasonably guessed.
	 */
	if (!VATTR_IS_SUPPORTED(vap, va_iosize))
		VATTR_RETURN(vap, va_iosize, vp->v_mount->mnt_vfsstat.f_iosize);
	
	if (!VATTR_IS_SUPPORTED(vap, va_flags))
		VATTR_RETURN(vap, va_flags, 0);

	if (!VATTR_IS_SUPPORTED(vap, va_filerev))
		VATTR_RETURN(vap, va_filerev, 0);

	if (!VATTR_IS_SUPPORTED(vap, va_gen))
		VATTR_RETURN(vap, va_gen, 0);

	/*
	 * Default sizes.  Ordering here is important, as later defaults build on earlier ones.
	 */
	if (!VATTR_IS_SUPPORTED(vap, va_data_size))
		VATTR_RETURN(vap, va_data_size, 0);

	/* do we want any of the possibly-computed values? */
	if (VATTR_IS_ACTIVE(vap, va_data_alloc) ||
	    VATTR_IS_ACTIVE(vap, va_total_size) ||
	    VATTR_IS_ACTIVE(vap, va_total_alloc)) {
                /* make sure f_bsize is valid */
                if (vp->v_mount->mnt_vfsstat.f_bsize == 0) {
                    if ((error = vfs_update_vfsstat(vp->v_mount, ctx, VFS_KERNEL_EVENT)) != 0)
                        goto out;
                }

		/* default va_data_alloc from va_data_size */
		if (!VATTR_IS_SUPPORTED(vap, va_data_alloc))
			VATTR_RETURN(vap, va_data_alloc, roundup(vap->va_data_size, vp->v_mount->mnt_vfsstat.f_bsize));

		/* default va_total_size from va_data_size */
		if (!VATTR_IS_SUPPORTED(vap, va_total_size))
			VATTR_RETURN(vap, va_total_size, vap->va_data_size);

		/* default va_total_alloc from va_total_size which is guaranteed at this point */
		if (!VATTR_IS_SUPPORTED(vap, va_total_alloc))
			VATTR_RETURN(vap, va_total_alloc, roundup(vap->va_total_size, vp->v_mount->mnt_vfsstat.f_bsize));
	}

	/*
	 * If we don't have a change time, pull it from the modtime.
	 */
	if (!VATTR_IS_SUPPORTED(vap, va_change_time) && VATTR_IS_SUPPORTED(vap, va_modify_time))
		VATTR_RETURN(vap, va_change_time, vap->va_modify_time);

	/*
	 * This is really only supported for the creation VNOPs, but since the field is there
	 * we should populate it correctly.
	 */
	VATTR_RETURN(vap, va_type, vp->v_type);

	/*
	 * The fsid can be obtained from the mountpoint directly.
	 */
	VATTR_RETURN(vap, va_fsid, vp->v_mount->mnt_vfsstat.f_fsid.val[0]);

out:

	return(error);
}