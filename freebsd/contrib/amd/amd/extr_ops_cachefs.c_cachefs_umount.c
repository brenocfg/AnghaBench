#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mf_flags; scalar_t__ mf_private; int /*<<< orphan*/  mf_mount; } ;
typedef  TYPE_1__ mntfs ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int AMU_UMOUNT_AUTOFS ; 
 int MFF_ON_AUTOFS ; 
 int UMOUNT_FS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
cachefs_umount(am_node *am, mntfs *mf)
{
  int unmount_flags = (mf->mf_flags & MFF_ON_AUTOFS) ? AMU_UMOUNT_AUTOFS : 0;
  int error;

  error = UMOUNT_FS(mf->mf_mount, mnttab_file_name, unmount_flags);

  /*
   * In the case of cachefs, we must fsck the cache directory.  Otherwise,
   * it will remain inconsistent, and the next cachefs mount will fail
   * with the error "no space left on device" (ENOSPC).
   *
   * XXX: this is hacky! use fork/exec/wait instead...
   */
  if (!error) {
    char *cachedir = NULL;
    char cmd[128];

    cachedir = (char *) mf->mf_private;
    plog(XLOG_INFO, "running fsck on cache directory \"%s\"", cachedir);
    xsnprintf(cmd, sizeof(cmd), "fsck -F cachefs %s", cachedir);
    system(cmd);
  }

  return error;
}