#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  opaque_t ;
struct TYPE_20__ {int mf_flags; int mf_refc; int mf_fsflags; int /*<<< orphan*/  mf_mount; TYPE_12__* mf_server; } ;
typedef  TYPE_6__ mntfs ;
struct TYPE_21__ {int /*<<< orphan*/  am_path; TYPE_5__* am_parent; TYPE_1__* am_al; } ;
typedef  TYPE_7__ am_node ;
struct TYPE_13__ {scalar_t__ nt_seconds; } ;
struct TYPE_16__ {TYPE_10__ na_mtime; } ;
struct TYPE_17__ {TYPE_2__ ns_attr_u; } ;
struct TYPE_18__ {TYPE_3__ ns_u; } ;
struct TYPE_19__ {TYPE_4__ am_attr; } ;
struct TYPE_15__ {TYPE_6__* al_mnt; } ;
struct TYPE_14__ {int /*<<< orphan*/  fs_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMQ_UMNT_SERVER ; 
 int /*<<< orphan*/  FSRV_ISUP (TYPE_12__*) ; 
 int FS_UBACKGROUND ; 
 int MFF_IS_AUTOFS ; 
 int MFF_LOGDOWN ; 
 int MFF_MOUNTED ; 
 int MFF_ON_AUTOFS ; 
 int MFF_UNMOUNTING ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  XLOG_STATS ; 
 int /*<<< orphan*/  autofs_release_mp (TYPE_7__*) ; 
 int /*<<< orphan*/  clocktime (TYPE_10__*) ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 int /*<<< orphan*/  free_map_if_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_child (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  run_task (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmount_node (int /*<<< orphan*/ ) ; 

int
unmount_mp(am_node *mp)
{
  int was_backgrounded = 0;
  mntfs *mf = mp->am_al->al_mnt;

#ifdef notdef
  plog(XLOG_INFO, "\"%s\" on %s timed out (flags 0x%x)",
       mp->am_path, mf->mf_mount, (int) mf->mf_flags);
#endif /* notdef */

#ifndef MNT2_NFS_OPT_SYMTTL
    /*
     * This code is needed to defeat Solaris 2.4's (and newer) symlink
     * values cache.  It forces the last-modified time of the symlink to be
     * current.  It is not needed if the O/S has an nfs flag to turn off the
     * symlink-cache at mount time (such as Irix 5.x and 6.x). -Erez.
     *
     * Additionally, Linux currently ignores the nt_useconds field,
     * so we must update the nt_seconds field every time if clocktime(NULL)
     * didn't return a new number of seconds.
     */
  if (mp->am_parent) {
    time_t last = mp->am_parent->am_attr.ns_u.ns_attr_u.na_mtime.nt_seconds;
    clocktime(&mp->am_parent->am_attr.ns_u.ns_attr_u.na_mtime);
    /* defensive programming... can't we assert the above condition? */
    if (last == (time_t) mp->am_parent->am_attr.ns_u.ns_attr_u.na_mtime.nt_seconds)
      mp->am_parent->am_attr.ns_u.ns_attr_u.na_mtime.nt_seconds++;
  }
#endif /* not MNT2_NFS_OPT_SYMTTL */

  if (mf->mf_refc == 1 && !FSRV_ISUP(mf->mf_server)) {
    /*
     * Don't try to unmount from a server that is known to be down
     */
    if (!(mf->mf_flags & MFF_LOGDOWN)) {
      /* Only log this once, otherwise gets a bit boring */
      plog(XLOG_STATS, "file server %s is down - timeout of \"%s\" ignored", mf->mf_server->fs_host, mp->am_path);
      mf->mf_flags |= MFF_LOGDOWN;
    }
    notify_child(mp, AMQ_UMNT_SERVER, 0, 0);
    return 0;
  }

  dlog("\"%s\" on %s timed out", mp->am_path, mf->mf_mount);
  mf->mf_flags |= MFF_UNMOUNTING;

#ifdef HAVE_FS_AUTOFS
  if (mf->mf_flags & MFF_IS_AUTOFS)
    autofs_release_mp(mp);
#endif /* HAVE_FS_AUTOFS */

  if ((mf->mf_fsflags & FS_UBACKGROUND) &&
      (mf->mf_flags & MFF_MOUNTED) &&
     !(mf->mf_flags & MFF_ON_AUTOFS)) {
    dlog("Trying unmount in background");
    run_task(unmount_node, (opaque_t) mp,
	     free_map_if_success, (opaque_t) mp);
    was_backgrounded = 1;
  } else {
    dlog("Trying unmount in foreground");
    free_map_if_success(unmount_node((opaque_t) mp), 0, (opaque_t) mp);
    dlog("unmount attempt done");
  }

  return was_backgrounded;
}