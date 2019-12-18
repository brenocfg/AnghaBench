#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* mnt; struct TYPE_9__* mnext; } ;
typedef  TYPE_2__ mntlist ;
struct TYPE_10__ {int mf_flags; int /*<<< orphan*/  mf_mount; } ;
typedef  TYPE_3__ mntfs ;
typedef  int /*<<< orphan*/  am_node ;
struct TYPE_8__ {char* mnt_dir; } ;

/* Variables and functions */
 int AMU_UMOUNT_AUTOFS ; 
 int EBUSY ; 
 int ENOENT ; 
 scalar_t__ Finishing ; 
 int MFF_ON_AUTOFS ; 
 int UMOUNT_FS (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 scalar_t__ amd_state ; 
 int amfs_host_mount (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ directory_prefix (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  discard_mntlist (TYPE_2__*) ; 
 int /*<<< orphan*/  dlog (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_2__* read_mtab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmdirs (char*) ; 
 int /*<<< orphan*/  unlock_mntlist () ; 

__attribute__((used)) static int
amfs_host_umount(am_node *am, mntfs *mf)
{
  mntlist *ml, *mprev;
  int unmount_flags = (mf->mf_flags & MFF_ON_AUTOFS) ? AMU_UMOUNT_AUTOFS : 0;
  int xerror = 0;

  /*
   * Read the mount list
   */
  mntlist *mlist = read_mtab(mf->mf_mount, mnttab_file_name);

#ifdef MOUNT_TABLE_ON_FILE
  /*
   * Unlock the mount list
   */
  unlock_mntlist();
#endif /* MOUNT_TABLE_ON_FILE */

  /*
   * Reverse list...
   */
  ml = mlist;
  mprev = NULL;
  while (ml) {
    mntlist *ml2 = ml->mnext;
    ml->mnext = mprev;
    mprev = ml;
    ml = ml2;
  }
  mlist = mprev;

  /*
   * Unmount all filesystems...
   */
  for (ml = mlist; ml && !xerror; ml = ml->mnext) {
    char *dir = ml->mnt->mnt_dir;
    if (directory_prefix(mf->mf_mount, dir)) {
      int error;
      dlog("amfs_host: unmounts %s", dir);
      /*
       * Unmount "dir"
       */
      error = UMOUNT_FS(dir, mnttab_file_name, unmount_flags);
      /*
       * Keep track of errors
       */
      if (error) {
	/*
	 * If we have not already set xerror and error is not ENOENT,
	 * then set xerror equal to error and log it.
	 * 'xerror' is the return value for this function.
	 *
	 * We do not want to pass ENOENT as an error because if the
	 * directory does not exists our work is done anyway.
	 */
	if (!xerror && error != ENOENT)
	  xerror = error;
	if (error != EBUSY) {
	  errno = error;
	  plog(XLOG_ERROR, "Tree unmount of %s failed: %m", ml->mnt->mnt_dir);
	}
      } else {
	(void) rmdirs(dir);
      }
    }
  }

  /*
   * Throw away mount list
   */
  discard_mntlist(mlist);

  /*
   * Try to remount, except when we are shutting down.
   */
  if (xerror && amd_state != Finishing) {
    xerror = amfs_host_mount(am, mf);
    if (!xerror) {
      /*
       * Don't log this - it's usually too verbose
       plog(XLOG_INFO, "Remounted host %s", mf->mf_info);
       */
      xerror = EBUSY;
    }
  }
  return xerror;
}