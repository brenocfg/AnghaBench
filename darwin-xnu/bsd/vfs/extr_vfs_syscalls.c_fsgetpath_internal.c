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
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int user_ssize_t ;
typedef  int uint64_t ;
struct mount {int mnt_flag; int /*<<< orphan*/  mnt_vnodecovered; } ;
typedef  int /*<<< orphan*/  ino64_t ;
typedef  int /*<<< orphan*/  dbg_parms ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int BUILDPATH_CHECKACCESS ; 
 int BUILDPATH_CHECK_MOVED ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  KDBG_VFS_LOOKUP_FLAG_LOOKUP ; 
 int /*<<< orphan*/  LK_NOWAIT ; 
 int MNT_UNION ; 
 int NUMPARMS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VFS_ROOT (struct mount*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int VFS_VGET (struct mount*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int build_path (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kdebug_vfs_lookup (long*,int,void*,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_fsgetpath (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct mount* mount_lookupby_volfsid (int,int) ; 
 int /*<<< orphan*/  text ; 
 scalar_t__ vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_context_suser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 struct mount* vnode_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 

__attribute__((used)) static int fsgetpath_internal(
	vfs_context_t ctx, int volfs_id, uint64_t objid,
	vm_size_t bufsize, caddr_t buf, int *pathlen)
{
	int error;
	struct mount *mp = NULL;
	vnode_t vp;
	int length;
	int bpflags;
	/* maximum number of times to retry build_path */
	unsigned int retries = 0x10;

	if (bufsize > PAGE_SIZE) {
		return (EINVAL);
	}

	if (buf == NULL) {
		return (ENOMEM);
	}

retry:
	if ((mp = mount_lookupby_volfsid(volfs_id, 1)) == NULL) {
		error = ENOTSUP;  /* unexpected failure */
		return ENOTSUP;
	}

unionget:
	if (objid == 2) {
		error = VFS_ROOT(mp, &vp, ctx);
	} else {
		error = VFS_VGET(mp, (ino64_t)objid, &vp, ctx);
	}

	if (error == ENOENT && (mp->mnt_flag & MNT_UNION)) {
		/*
		 * If the fileid isn't found and we're in a union
		 * mount volume, then see if the fileid is in the
		 * mounted-on volume.
		 */
		struct mount *tmp = mp;
		mp = vnode_mount(tmp->mnt_vnodecovered);
		vfs_unbusy(tmp);
		if (vfs_busy(mp, LK_NOWAIT) == 0)
			goto unionget;
	} else {
		vfs_unbusy(mp);
	}

	if (error) {
		return error;
	}

#if CONFIG_MACF
	error = mac_vnode_check_fsgetpath(ctx, vp);
	if (error) {
		vnode_put(vp);
		return error;
	}
#endif

	/* Obtain the absolute path to this vnode. */
	bpflags = vfs_context_suser(ctx) ? BUILDPATH_CHECKACCESS : 0;
	bpflags |= BUILDPATH_CHECK_MOVED;
	error = build_path(vp, buf, bufsize, &length, bpflags, ctx);
	vnode_put(vp);

	if (error) {
		/* there was a race building the path, try a few more times */
		if (error == EAGAIN) {
			--retries;
			if (retries > 0)
				goto retry;

			error = ENOENT;
		}
		goto out;
	}

	AUDIT_ARG(text, buf);

	if (kdebug_enable) {
		long dbg_parms[NUMPARMS];
		int  dbg_namelen;

		dbg_namelen = (int)sizeof(dbg_parms);

        if (length < dbg_namelen) {
			memcpy((char *)dbg_parms, buf, length);
			memset((char *)dbg_parms + length, 0, dbg_namelen - length);

			dbg_namelen = length;
		} else {
			memcpy((char *)dbg_parms, buf + (length - dbg_namelen), dbg_namelen);
		}

		kdebug_vfs_lookup(dbg_parms, dbg_namelen, (void *)vp,
				KDBG_VFS_LOOKUP_FLAG_LOOKUP);
	}

	*pathlen = (user_ssize_t)length; /* may be superseded by error */

out:
	return (error);
}