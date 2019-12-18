#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vfsstatfs {int dummy; } ;
struct statfs64 {int dummy; } ;
struct getfsstat_struct {scalar_t__ count; scalar_t__ maxcount; int error; int flags; scalar_t__ sfsp; } ;
typedef  TYPE_1__* mount_t ;
struct TYPE_6__ {struct vfsstatfs mnt_vfsstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  KAUTH_DEBUG (char*,int) ; 
 int MNT_DWAIT ; 
 int MNT_NOWAIT ; 
 int MNT_WAIT ; 
 int VFS_RETURNED ; 
 int VFS_RETURNED_DONE ; 
 int /*<<< orphan*/  VFS_USER_EVENT ; 
 int mac_mount_check_stat (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int statfs64_common (TYPE_1__*,struct vfsstatfs*,scalar_t__) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vfs_update_vfsstat (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getfsstat64_callback(mount_t mp, void * arg)
{
	struct getfsstat_struct *fstp = (struct getfsstat_struct *)arg;
	struct vfsstatfs *sp;
	int error;

	if (fstp->sfsp && fstp->count < fstp->maxcount) {
#if CONFIG_MACF
		error = mac_mount_check_stat(vfs_context_current(), mp);
		if (error != 0) {
			fstp->error = error;
			return(VFS_RETURNED_DONE);
		}
#endif
		sp = &mp->mnt_vfsstat;
		/*
		 * If MNT_NOWAIT is specified, do not refresh the fsstat
		 * cache. MNT_WAIT overrides MNT_NOWAIT.
		 *
		 * We treat MNT_DWAIT as MNT_WAIT for all instances of
		 * getfsstat, since the constants are out of the same
		 * namespace.
		 */
		if (((fstp->flags & MNT_NOWAIT) == 0 ||
		     (fstp->flags & (MNT_WAIT | MNT_DWAIT))) &&
		    (error = vfs_update_vfsstat(mp, vfs_context_current(), VFS_USER_EVENT))) {
			KAUTH_DEBUG("vfs_update_vfsstat returned %d", error);
			return(VFS_RETURNED);
		}

		error = statfs64_common(mp, sp, fstp->sfsp);
		if (error) {
			fstp->error = error;
			return(VFS_RETURNED_DONE);
		}
		fstp->sfsp += sizeof(struct statfs64);
	}
	fstp->count++;
	return(VFS_RETURNED);
}