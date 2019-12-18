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
typedef  int /*<<< orphan*/  voidp ;
typedef  scalar_t__ opaque_t ;
struct TYPE_6__ {int mf_refc; int mf_flags; int mf_fsflags; int /*<<< orphan*/  mf_cid; int /*<<< orphan*/  mf_mount; TYPE_1__* mf_ops; scalar_t__ mf_error; int /*<<< orphan*/  mf_info; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_5__ {int /*<<< orphan*/  fs_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOWED_MOUNT_TIME ; 
 int FS_DISCARD ; 
 int MFF_MOUNTED ; 
 int MFF_MOUNTING ; 
 int MFF_RESTART ; 
 int MFF_RSTKEEP ; 
 int MFF_UNMOUNTING ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  discard_mntfs (TYPE_2__*) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*,int,...) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_2__*),int /*<<< orphan*/ ) ; 

void
free_mntfs(opaque_t arg)
{
  mntfs *mf = (mntfs *) arg;

  dlog("free_mntfs <%s> type %s mf_refc %d flags %x",
       mf->mf_mount, mf->mf_ops->fs_type, mf->mf_refc, mf->mf_flags);

  /*
   * We shouldn't ever be called to free something that has
   * a non-positive refcount.  Something is badly wrong if
   * we have been!  Ignore the request for now...
   */
  if (mf->mf_refc <= 0) {
    plog(XLOG_ERROR, "IGNORING free_mntfs for <%s>: refc %d, flags %x (bug?)",
         mf->mf_mount, mf->mf_refc, mf->mf_flags);
    return;
  }

  /* don't discard last reference of a restarted/kept mntfs */
  if (mf->mf_refc == 1 && mf->mf_flags & MFF_RSTKEEP) {
    plog(XLOG_ERROR, "IGNORING free_mntfs for <%s>: refc %d, flags %x (restarted)",
         mf->mf_mount, mf->mf_refc, mf->mf_flags);
    return;
  }

  if (--mf->mf_refc == 0) {
    if (mf->mf_flags & MFF_MOUNTED) {
      int quoted;
      mf->mf_flags &= ~MFF_MOUNTED;

      /*
       * Record for posterity
       */
      quoted = strchr(mf->mf_info, ' ') != 0;	/* cheap */
      plog(XLOG_INFO, "%s%s%s %sed fstype %s from %s",
	   quoted ? "\"" : "",
	   mf->mf_info,
	   quoted ? "\"" : "",
	   mf->mf_error ? "discard" : "unmount",
	   mf->mf_ops->fs_type, mf->mf_mount);
    }

    if (mf->mf_fsflags & FS_DISCARD) {
      dlog("Immediately discarding mntfs for %s", mf->mf_mount);
      discard_mntfs(mf);

    } else {

      if (mf->mf_flags & MFF_RESTART) {
	dlog("Discarding remount hook for %s", mf->mf_mount);
      } else {
	dlog("Discarding last mntfs reference to %s fstype %s",
	     mf->mf_mount, mf->mf_ops->fs_type);
      }
      if (mf->mf_flags & (MFF_MOUNTED | MFF_MOUNTING | MFF_UNMOUNTING))
	dlog("mntfs reference for %s still active", mf->mf_mount);
      mf->mf_cid = timeout(ALLOWED_MOUNT_TIME, discard_mntfs, (voidp) mf);
    }
  }
}