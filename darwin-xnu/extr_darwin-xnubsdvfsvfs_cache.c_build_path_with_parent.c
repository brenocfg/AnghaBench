#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {char* va_name; scalar_t__ va_parentid; } ;
typedef  int /*<<< orphan*/  ino64_t ;
struct TYPE_20__ {int v_flag; char* v_name; int v_id; TYPE_14__* v_mount; struct TYPE_20__* v_parent; } ;
struct TYPE_19__ {TYPE_2__* fd_rdir; } ;
struct TYPE_18__ {int mnt_flag; int mnt_kern_flag; TYPE_2__* mnt_vnodecovered; } ;
struct TYPE_17__ {TYPE_1__* p_fd; } ;

/* Variables and functions */
 int BUILDPATH_CHECKACCESS ; 
 int BUILDPATH_CHECK_MOVED ; 
 int BUILDPATH_NO_FS_ENTER ; 
 int BUILDPATH_VOLUME_RELATIVE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FREE_ZONE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_VNODE_SEARCH ; 
 int /*<<< orphan*/  MALLOC_ZONE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int MNTK_PATH_FROM_ID ; 
 int MNT_ROOTFS ; 
 int /*<<< orphan*/  M_NAMEI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NAME_CACHE_LOCK_SHARED () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 TYPE_2__* NULLVP ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VFS_VGET (TYPE_14__*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int VISHARDLINK ; 
 int /*<<< orphan*/  VNODE_UPDATE_NAME ; 
 int /*<<< orphan*/  VNODE_UPDATE_PARENT ; 
 int VROOT ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 TYPE_2__* rootvnode ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  va_name ; 
 int /*<<< orphan*/  va_parentid ; 
 TYPE_10__* vfs_context_proc (int /*<<< orphan*/ ) ; 
 int vnode_authorize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnode_getattr (TYPE_2__*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_getwithvid (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vnode_isdir (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_update_identity (TYPE_2__*,TYPE_2__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
build_path_with_parent(vnode_t first_vp, vnode_t parent_vp, char *buff, int buflen, int *outlen, int flags, vfs_context_t ctx)
{
        vnode_t vp, tvp;
	vnode_t vp_with_iocount;
        vnode_t proc_root_dir_vp;
	char *end;
	const char *str;
	int  len;
	int  ret = 0;
	int  fixhardlink;

	if (first_vp == NULLVP)
		return (EINVAL);
		
	if (buflen <= 1)
		return (ENOSPC);

	/*
	 * Grab the process fd so we can evaluate fd_rdir.
	 */
	if (vfs_context_proc(ctx)->p_fd)
		proc_root_dir_vp = vfs_context_proc(ctx)->p_fd->fd_rdir;
	else
		proc_root_dir_vp = NULL;

	vp_with_iocount = NULLVP;
again:
	vp = first_vp;

	end = &buff[buflen-1];
	*end = '\0';

	/*
	 * holding the NAME_CACHE_LOCK in shared mode is
	 * sufficient to stabilize both the vp->v_parent chain
	 * and the 'vp->v_mount->mnt_vnodecovered' chain
	 *
	 * if we need to drop this lock, we must first grab the v_id
	 * from the vnode we're currently working with... if that
	 * vnode doesn't already have an io_count reference (the vp
	 * passed in comes with one), we must grab a reference
	 * after we drop the NAME_CACHE_LOCK via vnode_getwithvid...
	 * deadlocks may result if you call vnode_get while holding
	 * the NAME_CACHE_LOCK... we lazily release the reference
	 * we pick up the next time we encounter a need to drop 
	 * the NAME_CACHE_LOCK or before we return from this routine
	 */
	NAME_CACHE_LOCK_SHARED();

	/*
	 * Check if this is the root of a file system.
	 */
	while (vp && vp->v_flag & VROOT) {
		if (vp->v_mount == NULL) {
			ret = EINVAL;
			goto out_unlock;
		}
	        if ((vp->v_mount->mnt_flag & MNT_ROOTFS) || (vp == proc_root_dir_vp)) {
			/*
			 * It's the root of the root file system, so it's
			 * just "/".
			 */
		        *--end = '/';

			goto out_unlock;
		} else {
			/* 
			 * This the root of the volume and the caller does not 
			 * want to cross mount points.  Therefore just return 
			 * '/' as the relative path. 
			 */
			if (flags & BUILDPATH_VOLUME_RELATIVE) {
				*--end = '/';
				goto out_unlock;
			} else {
				vp = vp->v_mount->mnt_vnodecovered;
			}
		}
	}

	while ((vp != NULLVP) && (vp->v_parent != vp)) {
		int  vid;

		/*
		 * For hardlinks the v_name may be stale, so if its OK
		 * to enter a file system, ask the file system for the
		 * name and parent (below).
		 */
		fixhardlink = (vp->v_flag & VISHARDLINK) &&
		              (vp->v_mount->mnt_kern_flag & MNTK_PATH_FROM_ID) &&
		              !(flags & BUILDPATH_NO_FS_ENTER);

		if (!fixhardlink) {
			str = vp->v_name;

			if (str == NULL || *str == '\0') {
				if (vp->v_parent != NULL)
					ret = EINVAL;
				else
					ret = ENOENT;
				goto out_unlock;
			}
			len = strlen(str);
			/*
			 * Check that there's enough space (including space for the '/')
			 */
			if ((end - buff) < (len + 1)) {
				ret = ENOSPC;
				goto out_unlock;
			}
			/*
			 * Copy the name backwards.
			 */
			str += len;
	
			for (; len > 0; len--)
			       *--end = *--str;
			/*
			 * Add a path separator.
			 */
			*--end = '/';
		}

		/*
		 * Walk up the parent chain.
		 */
		if (((vp->v_parent != NULLVP) && !fixhardlink) ||
				(flags & BUILDPATH_NO_FS_ENTER)) {

			/*
			 * In this if () block we are not allowed to enter the filesystem
			 * to conclusively get the most accurate parent identifier.
			 * As a result, if 'vp' does not identify '/' and it
			 * does not have a valid v_parent, then error out
			 * and disallow further path construction
			 */
			if ((vp->v_parent == NULLVP) && (rootvnode != vp)) {
				/*
				 * Only '/' is allowed to have a NULL parent
				 * pointer. Upper level callers should ideally
				 * re-drive name lookup on receiving a ENOENT.
				 */
				ret = ENOENT;

				/* The code below will exit early if 'tvp = vp' == NULL */
			}
			vp = vp->v_parent;

			/*
			 * if the vnode we have in hand isn't a directory and it
			 * has a v_parent, then we started with the resource fork
			 * so skip up to avoid getting a duplicate copy of the
			 * file name in the path.
			 */
			if (vp && !vnode_isdir(vp) && vp->v_parent) {
				vp = vp->v_parent;
			}
		} else {
			/*
			 * No parent, go get it if supported.
			 */
			struct vnode_attr  va;
			vnode_t  dvp;

			/*
			 * Make sure file system supports obtaining a path from id.
			 */
			if (!(vp->v_mount->mnt_kern_flag & MNTK_PATH_FROM_ID)) {
				ret = ENOENT;
				goto out_unlock;
			}
			vid = vp->v_id;

			NAME_CACHE_UNLOCK();

			if (vp != first_vp && vp != parent_vp && vp != vp_with_iocount) {
				if (vp_with_iocount) {
					vnode_put(vp_with_iocount);
					vp_with_iocount = NULLVP;
				}
				if (vnode_getwithvid(vp, vid))
					goto again;
				vp_with_iocount = vp;
			}
			VATTR_INIT(&va);
			VATTR_WANTED(&va, va_parentid);

			if (fixhardlink) {
				VATTR_WANTED(&va, va_name);
				MALLOC_ZONE(va.va_name, caddr_t, MAXPATHLEN, M_NAMEI, M_WAITOK);
			} else {
				va.va_name = NULL;
			}
			/*
			 * Ask the file system for its parent id and for its name (optional).
			 */
			ret = vnode_getattr(vp, &va, ctx);

			if (fixhardlink) {
				if ((ret == 0) && (VATTR_IS_SUPPORTED(&va, va_name))) {
					str = va.va_name;
					vnode_update_identity(vp, NULL, str, strlen(str), 0, VNODE_UPDATE_NAME);
				} else if (vp->v_name) {
					str = vp->v_name;
					ret = 0;
				} else {
					ret = ENOENT;
					goto bad_news;
				}
				len = strlen(str);

				/*
				 * Check that there's enough space.
				 */
				if ((end - buff) < (len + 1)) {
					ret = ENOSPC;
				} else {
					/* Copy the name backwards. */
					str += len;

					for (; len > 0; len--) {
						*--end = *--str;
					}
					/*
					 * Add a path separator.
					 */
					*--end = '/';
				}
bad_news:
				FREE_ZONE(va.va_name, MAXPATHLEN, M_NAMEI);
			}
			if (ret || !VATTR_IS_SUPPORTED(&va, va_parentid)) {
				ret = ENOENT;
				goto out;
			}
			/*
			 * Ask the file system for the parent vnode.
			 */
			if ((ret = VFS_VGET(vp->v_mount, (ino64_t)va.va_parentid, &dvp, ctx)))
				goto out;

			if (!fixhardlink && (vp->v_parent != dvp))
				vnode_update_identity(vp, dvp, NULL, 0, 0, VNODE_UPDATE_PARENT);

			if (vp_with_iocount)
				vnode_put(vp_with_iocount);
			vp = dvp;
			vp_with_iocount = vp;

			NAME_CACHE_LOCK_SHARED();

			/*
			 * if the vnode we have in hand isn't a directory and it
			 * has a v_parent, then we started with the resource fork
			 * so skip up to avoid getting a duplicate copy of the
			 * file name in the path.
			 */
			if (vp && !vnode_isdir(vp) && vp->v_parent)
				vp = vp->v_parent;
		}

		if (vp && (flags & BUILDPATH_CHECKACCESS)) {
			vid = vp->v_id;

			NAME_CACHE_UNLOCK();

			if (vp != first_vp && vp != parent_vp && vp != vp_with_iocount) {
				if (vp_with_iocount) {
					vnode_put(vp_with_iocount);
					vp_with_iocount = NULLVP;
				}
				if (vnode_getwithvid(vp, vid))
					goto again;
				vp_with_iocount = vp;
			}
			if ((ret = vnode_authorize(vp, NULL, KAUTH_VNODE_SEARCH, ctx)))
				goto out;  	/* no peeking */

			NAME_CACHE_LOCK_SHARED();
		}

		/*
		 * When a mount point is crossed switch the vp.
		 * Continue until we find the root or we find
		 * a vnode that's not the root of a mounted
		 * file system.
		 */
		tvp = vp;

		while (tvp) {
			if (tvp == proc_root_dir_vp)
				goto out_unlock;	/* encountered the root */

			if (!(tvp->v_flag & VROOT) || !tvp->v_mount)
				break;			/* not the root of a mounted FS */

			if (flags & BUILDPATH_VOLUME_RELATIVE) {
				/* Do not cross over mount points */
				tvp = NULL;
			} else {
				tvp = tvp->v_mount->mnt_vnodecovered;
			}
		}
		if (tvp == NULLVP)
			goto out_unlock;
		vp = tvp;
	}
out_unlock:
	NAME_CACHE_UNLOCK();
out:
	if (vp_with_iocount)
		vnode_put(vp_with_iocount);
	/*
	 * Slide the name down to the beginning of the buffer.
	 */
	memmove(buff, end, &buff[buflen] - end);

	/*
	 * length includes the trailing zero byte
	 */
	*outlen = &buff[buflen] - end;
 
	/* One of the parents was moved during path reconstruction. 
	 * The caller is interested in knowing whether any of the 
	 * parents moved via BUILDPATH_CHECK_MOVED, so return EAGAIN.
	 */
	if ((ret == ENOENT) && (flags & BUILDPATH_CHECK_MOVED)) {
		ret = EAGAIN;
	}

	return (ret);
}