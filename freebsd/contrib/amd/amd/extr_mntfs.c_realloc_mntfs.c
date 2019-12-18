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
struct TYPE_6__ {int mf_refc; int mf_flags; int /*<<< orphan*/  mf_server; int /*<<< orphan*/ * mf_ops; int /*<<< orphan*/  mf_mount; } ;
typedef  TYPE_1__ mntfs ;
typedef  int /*<<< orphan*/  am_opts ;
typedef  int /*<<< orphan*/  am_ops ;

/* Variables and functions */
 int /*<<< orphan*/  FSRV_ISDOWN (int /*<<< orphan*/ ) ; 
 int MFF_MOUNTED ; 
 int MFF_RESTART ; 
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  amfs_error_ops ; 
 TYPE_1__* find_mntfs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free_mntfs (TYPE_1__*) ; 

mntfs *
realloc_mntfs(mntfs *mf, am_ops *ops, am_opts *mo, char *mp, char *info, char *auto_opts, char *mopts, char *remopts)
{
  mntfs *mf2;

  if (mf->mf_refc == 1 &&
      mf->mf_flags & MFF_RESTART &&
      STREQ(mf->mf_mount, mp)) {
    /*
     * If we are inheriting then just return
     * the same node...
     */
    return mf;
  }

  /*
   * Re-use the existing mntfs if it is mounted.
   * This traps a race in nfsx.
   */
  if (mf->mf_ops != &amfs_error_ops &&
      (mf->mf_flags & MFF_MOUNTED) &&
      !FSRV_ISDOWN(mf->mf_server)) {
    return mf;
  }

  mf2 = find_mntfs(ops, mo, mp, info, auto_opts, mopts, remopts);
  free_mntfs(mf);
  return mf2;
}