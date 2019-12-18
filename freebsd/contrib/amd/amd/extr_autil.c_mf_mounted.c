#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mf_flags; int /*<<< orphan*/  mf_mount; TYPE_1__* mf_ops; int /*<<< orphan*/  mf_info; scalar_t__ mf_error; } ;
typedef  TYPE_2__ mntfs ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {int /*<<< orphan*/  fs_type; int /*<<< orphan*/  (* mounted ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int MFF_MOUNTED ; 
 int MFF_RESTART ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
mf_mounted(mntfs *mf, bool_t call_free_opts)
{
  int quoted;
  int wasmounted = mf->mf_flags & MFF_MOUNTED;

  if (!wasmounted) {
    /*
     * If this is a freshly mounted
     * filesystem then update the
     * mntfs structure...
     */
    mf->mf_flags |= MFF_MOUNTED;
    mf->mf_error = 0;

    /*
     * Do mounted callback
     */
    if (mf->mf_ops->mounted)
      mf->mf_ops->mounted(mf);

    /*
     * We used to free the mf_mo (options) here, however they're now stored
     * and managed with the mntfs and do not need to be free'd here (this ensures
     * that we use the same options to monitor/unmount the system as we used
     * to mount it).
     */
  }

  if (mf->mf_flags & MFF_RESTART) {
    mf->mf_flags &= ~MFF_RESTART;
    dlog("Restarted filesystem %s, flags 0x%x", mf->mf_mount, mf->mf_flags);
  }

  /*
   * Log message
   */
  quoted = strchr(mf->mf_info, ' ') != 0;
  plog(XLOG_INFO, "%s%s%s %s fstype %s on %s",
       quoted ? "\"" : "",
       mf->mf_info,
       quoted ? "\"" : "",
       wasmounted ? "referenced" : "mounted",
       mf->mf_ops->fs_type, mf->mf_mount);
}