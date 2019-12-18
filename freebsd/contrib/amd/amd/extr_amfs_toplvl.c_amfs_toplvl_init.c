#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mf_mount; } ;
typedef  TYPE_1__ mntfs ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int AMU_UMOUNT_DETACH ; 
 int AMU_UMOUNT_FORCE ; 
 int CFM_FORCED_UNMOUNTS ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  dlog (char*) ; 
 TYPE_2__ gopt ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int umount2_fs (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
amfs_toplvl_init(mntfs *mf)
{
  int error = 0;

#if (defined(MNT2_GEN_OPT_FORCE) || defined(MNT2_GEN_OPT_DETACH)) && (defined(HAVE_UVMOUNT) || defined(HAVE_UMOUNT2))
  if (gopt.flags & CFM_FORCED_UNMOUNTS) {
    plog(XLOG_INFO, "amfs_toplvl_init: trying forced/lazy unmount of %s",
	 mf->mf_mount);
    error = umount2_fs(mf->mf_mount, AMU_UMOUNT_FORCE | AMU_UMOUNT_DETACH);
    if (error)
      plog(XLOG_INFO, "amfs_toplvl_init: forced/lazy unmount failed: %m");
    else
      dlog("amfs_toplvl_init: forced/lazy unmount succeeded");
  }
#endif /* (MNT2_GEN_OPT_FORCE || MNT2_GEN_OPT_DETACH) && (HAVE_UVMOUNT || HAVE_UMOUNT2) */
  return error;
}