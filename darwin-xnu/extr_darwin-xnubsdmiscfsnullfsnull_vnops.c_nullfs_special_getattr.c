#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vnode_t ;
struct vnop_getattr_args {scalar_t__ a_vp; TYPE_8__* a_vap; int /*<<< orphan*/  a_context; } ;
struct TYPE_16__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_14__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_13__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct vnode_attr {int va_uid; int va_gid; TYPE_6__ va_access_time; TYPE_4__ va_modify_time; TYPE_3__ va_create_time; } ;
struct null_mount {scalar_t__ nullm_secondvp; int /*<<< orphan*/  nullm_lowerrootvid; int /*<<< orphan*/ * nullm_lowerrootvp; } ;
typedef  int /*<<< orphan*/  mount_t ;
typedef  int ino_t ;
struct TYPE_15__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_12__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_18__ {TYPE_5__ va_modify_time; TYPE_2__ va_create_time; } ;
struct TYPE_11__ {int* val; } ;
struct TYPE_17__ {int f_iosize; TYPE_1__ f_fsid; } ;

/* Variables and functions */
 int EIO ; 
 struct null_mount* MOUNTTONULLMOUNT (int /*<<< orphan*/ ) ; 
 int NULL_ROOT_INO ; 
 int NULL_SECOND_INO ; 
 int S_IFDIR ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int UF_HIDDEN ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 scalar_t__ VATTR_IS_ACTIVE (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_RETURN (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VATTR_SET_SUPPORTED (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  va_create_time ; 
 int /*<<< orphan*/  va_data_alloc ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_fileid ; 
 int /*<<< orphan*/  va_filerev ; 
 int /*<<< orphan*/  va_flags ; 
 int /*<<< orphan*/  va_fsid ; 
 int /*<<< orphan*/  va_gen ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_iosize ; 
 int /*<<< orphan*/  va_linkid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_modify_time ; 
 int /*<<< orphan*/  va_nlink ; 
 int /*<<< orphan*/  va_parentid ; 
 int /*<<< orphan*/  va_rdev ; 
 int /*<<< orphan*/  va_total_size ; 
 int /*<<< orphan*/  va_type ; 
 int /*<<< orphan*/  va_uid ; 
 TYPE_7__* vfs_statfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vfs_vnodecovered (int /*<<< orphan*/ ) ; 
 int vnode_getattr (int /*<<< orphan*/ *,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_getwithvid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (scalar_t__) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ *) ; 
 int vnode_vtype (scalar_t__) ; 

__attribute__((used)) static int
nullfs_special_getattr(struct vnop_getattr_args * args)
{
	mount_t mp                  = vnode_mount(args->a_vp);
	struct null_mount * null_mp = MOUNTTONULLMOUNT(mp);

	ino_t ino = NULL_ROOT_INO;
	struct vnode_attr covered_rootattr;
	vnode_t checkvp = null_mp->nullm_lowerrootvp;

	VATTR_INIT(&covered_rootattr);
	VATTR_WANTED(&covered_rootattr, va_uid);
	VATTR_WANTED(&covered_rootattr, va_gid);
	VATTR_WANTED(&covered_rootattr, va_create_time);
	VATTR_WANTED(&covered_rootattr, va_modify_time);
	VATTR_WANTED(&covered_rootattr, va_access_time);

	/* prefer to get this from the lower root vp, but if not (i.e. forced unmount
	 * of lower fs) try the mount point covered vnode */
	if (vnode_getwithvid(checkvp, null_mp->nullm_lowerrootvid)) {
		checkvp = vfs_vnodecovered(mp);
		if (checkvp == NULL) {
			return EIO;
		}
	}

	int error = vnode_getattr(checkvp, &covered_rootattr, args->a_context);

	vnode_put(checkvp);
	if (error) {
		/* we should have been able to get attributes fore one of the two choices so
		 * fail if we didn't */
		return error;
	}

	/* we got the attributes of the vnode we cover so plow ahead */
	if (args->a_vp == null_mp->nullm_secondvp) {
		ino = NULL_SECOND_INO;
	}

	VATTR_RETURN(args->a_vap, va_type, vnode_vtype(args->a_vp));
	VATTR_RETURN(args->a_vap, va_rdev, 0);
	VATTR_RETURN(args->a_vap, va_nlink, 3);      /* always just ., .., and the child */
	VATTR_RETURN(args->a_vap, va_total_size, 0); // hoping this is ok

	VATTR_RETURN(args->a_vap, va_data_size, 0); // hoping this is ok
	VATTR_RETURN(args->a_vap, va_data_alloc, 0);
	VATTR_RETURN(args->a_vap, va_iosize, vfs_statfs(mp)->f_iosize);
	VATTR_RETURN(args->a_vap, va_fileid, ino);
	VATTR_RETURN(args->a_vap, va_linkid, ino);
	VATTR_RETURN(args->a_vap, va_fsid, vfs_statfs(mp)->f_fsid.val[0]); // return the fsid of the mount point
	VATTR_RETURN(args->a_vap, va_filerev, 0);
	VATTR_RETURN(args->a_vap, va_gen, 0);
	VATTR_RETURN(args->a_vap, va_flags, UF_HIDDEN); /* mark our fake directories as hidden. People
	                                                   shouldn't be enocouraged to poke around in them */

	if (ino == NULL_SECOND_INO) {
		VATTR_RETURN(args->a_vap, va_parentid, NULL_ROOT_INO); /* no parent at the root, so
		                                                          the only other vnode that
		                                                          goes through this path is
		                                                          second and its parent is
		                                                          1.*/
	}

	if (VATTR_IS_ACTIVE(args->a_vap, va_mode)) {
		/* force dr_xr_xr_x */
		VATTR_RETURN(args->a_vap, va_mode, S_IFDIR | S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}
	if (VATTR_IS_ACTIVE(args->a_vap, va_uid)) {
		VATTR_RETURN(args->a_vap, va_uid, covered_rootattr.va_uid);
	}
	if (VATTR_IS_ACTIVE(args->a_vap, va_gid)) {
		VATTR_RETURN(args->a_vap, va_gid, covered_rootattr.va_gid);
	}

	if (VATTR_IS_ACTIVE(args->a_vap, va_create_time)) {
		VATTR_SET_SUPPORTED(args->a_vap, va_create_time);
		args->a_vap->va_create_time.tv_sec  = covered_rootattr.va_create_time.tv_sec;
		args->a_vap->va_create_time.tv_nsec = covered_rootattr.va_create_time.tv_nsec;
	}
	if (VATTR_IS_ACTIVE(args->a_vap, va_modify_time)) {
		VATTR_SET_SUPPORTED(args->a_vap, va_modify_time);
		args->a_vap->va_modify_time.tv_sec  = covered_rootattr.va_modify_time.tv_sec;
		args->a_vap->va_modify_time.tv_nsec = covered_rootattr.va_modify_time.tv_nsec;
	}
	if (VATTR_IS_ACTIVE(args->a_vap, va_access_time)) {
		VATTR_SET_SUPPORTED(args->a_vap, va_access_time);
		args->a_vap->va_modify_time.tv_sec  = covered_rootattr.va_access_time.tv_sec;
		args->a_vap->va_modify_time.tv_nsec = covered_rootattr.va_access_time.tv_nsec;
	}

	return 0;
}