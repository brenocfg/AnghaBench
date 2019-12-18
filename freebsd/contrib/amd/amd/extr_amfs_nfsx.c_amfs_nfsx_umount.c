#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct amfs_nfsx {int nx_c; TYPE_3__* nx_v; } ;
struct TYPE_10__ {int mf_fsflags; int /*<<< orphan*/  mf_flags; int /*<<< orphan*/  mf_mount; TYPE_1__* mf_ops; scalar_t__ mf_private; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_11__ {int n_error; TYPE_2__* n_mnt; } ;
typedef  TYPE_3__ amfs_nfsx_mnt ;
typedef  int /*<<< orphan*/  am_node ;
struct TYPE_9__ {int (* umount_fs ) (int /*<<< orphan*/ *,TYPE_2__*) ;int /*<<< orphan*/  (* umounted ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int FS_MKMNT ; 
 int /*<<< orphan*/  MFF_MKMNT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int amfs_nfsx_remount (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free_mntfs (TYPE_2__*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmdirs (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static int
amfs_nfsx_umount(am_node *am, mntfs *mf)
{
  struct amfs_nfsx *nx = (struct amfs_nfsx *) mf->mf_private;
  amfs_nfsx_mnt *n;
  int glob_error = 0;

  /*
   * Iterate in reverse through the mntfs's and unmount each filesystem
   * which is mounted.
   */
  for (n = nx->nx_v + nx->nx_c - 1; n >= nx->nx_v; --n) {
    mntfs *m = n->n_mnt;
    /*
     * If this node has not been messed with
     * and there has been no error so far
     * then try and unmount.
     * If an error had occurred then zero
     * the error code so that the remount
     * only tries to unmount those nodes
     * which had been successfully unmounted.
     */
    if (n->n_error == 0) {
      dlog("calling underlying fumount on %s", m->mf_mount);
      n->n_error = m->mf_ops->umount_fs(am, m);
      if (n->n_error) {
	glob_error = n->n_error;
	n->n_error = 0;
      } else {
	/*
	 * Make sure remount gets this node
	 */
	n->n_error = -1;
      }
    }
  }

  /*
   * If any unmounts failed then remount the
   * whole lot...
   */
  if (glob_error) {
    glob_error = amfs_nfsx_remount(am, mf, TRUE);
    if (glob_error) {
      errno = glob_error;	/* XXX */
      plog(XLOG_USER, "amfs_nfsx: remount of %s failed: %m", mf->mf_mount);
    }
    glob_error = EBUSY;
  } else {
    /*
     * Remove all the mount points
     */
    for (n = nx->nx_v; n < nx->nx_v + nx->nx_c; n++) {
      mntfs *m = n->n_mnt;
      dlog("calling underlying umounted on %s", m->mf_mount);
      if (m->mf_ops->umounted)
	m->mf_ops->umounted(m);

      if (n->n_error < 0) {
	if (m->mf_fsflags & FS_MKMNT) {
	  (void) rmdirs(m->mf_mount);
	  m->mf_flags &= ~MFF_MKMNT;
	}
      }
      free_mntfs(m);
      n->n_mnt = NULL;
      n->n_error = -1;
    }
  }

  return glob_error;
}