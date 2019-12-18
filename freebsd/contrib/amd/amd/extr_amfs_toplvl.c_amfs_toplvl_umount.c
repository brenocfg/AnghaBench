#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
struct TYPE_6__ {int mf_flags; } ;
typedef  TYPE_1__ mntfs ;
struct TYPE_7__ {int /*<<< orphan*/  am_path; } ;
typedef  TYPE_2__ am_node ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int AMU_UMOUNT_AUTOFS ; 
 int AMU_UMOUNT_DETACH ; 
 int AMU_UMOUNT_FORCE ; 
 int CFM_FORCED_UNMOUNTS ; 
 int EBUSY ; 
 int ENOTDIR ; 
 int MFF_IS_AUTOFS ; 
 int MFF_ON_AUTOFS ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int UMOUNT_FS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 TYPE_3__ gopt ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 

int
amfs_toplvl_umount(am_node *mp, mntfs *mf)
{
  struct stat stb;
  int unmount_flags = (mf->mf_flags & MFF_ON_AUTOFS) ? AMU_UMOUNT_AUTOFS : 0;
  int error;
  int count = 0;		/* how many times did we try to unmount? */

again:
  /*
   * The lstat is needed if this mount is type=direct.
   * When that happens, the kernel cache gets confused
   * between the underlying type (dir) and the mounted
   * type (link) and so needs to be re-synced before
   * the unmount.  This is all because the unmount system
   * call follows links and so can't actually unmount
   * a link (stupid!).  It was noted that doing an ls -ld
   * of the mount point to see why things were not working
   * actually fixed the problem - so simulate an ls -ld here.
   */
  if (lstat(mp->am_path, &stb) < 0) {
    error = errno;
    dlog("lstat(%s): %m", mp->am_path);
    goto out;
  }
  if ((stb.st_mode & S_IFMT) != S_IFDIR) {
    plog(XLOG_ERROR, "amfs_toplvl_umount: %s is not a directory, aborting.", mp->am_path);
    error = ENOTDIR;
    goto out;
  }

  error = UMOUNT_FS(mp->am_path, mnttab_file_name, unmount_flags);
  if (error == EBUSY) {
#ifdef HAVE_FS_AUTOFS
    /*
     * autofs mounts are "in place", so it is possible
     * that we can't just unmount our mount points and go away.
     * If that's the case, just give up.
     */
    if (mf->mf_flags & MFF_IS_AUTOFS)
      return error;
#endif /* HAVE_FS_AUTOFS */
    plog(XLOG_WARNING, "amfs_toplvl_unmount retrying %s in 1s", mp->am_path);
    count++;
    sleep(1);
    /*
     * If user wants forced/lazy unmount semantics, then set those flags,
     * but only after we've tried normal lstat/umount a few times --
     * otherwise forced unmounts may hang this very same Amd (by preventing
     * it from achieving a clean unmount).
     */
    if (gopt.flags & CFM_FORCED_UNMOUNTS) {
      if (count == 5) {		/* after 5 seconds, try MNT_FORCE */
	dlog("enabling forced unmounts for toplvl node %s", mp->am_path);
	unmount_flags |= AMU_UMOUNT_FORCE;
      }
      if (count == 10) {	/* after 10 seconds, try MNT_DETACH */
	dlog("enabling detached unmounts for toplvl node %s", mp->am_path);
	unmount_flags |= AMU_UMOUNT_DETACH;
      }
    }
    goto again;
  }
out:
  return error;
}