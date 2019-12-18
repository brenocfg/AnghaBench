#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchan_t ;
typedef  scalar_t__ opaque_t ;
struct TYPE_11__ {int mf_flags; int mf_mount; int /*<<< orphan*/ * mf_ops; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_12__ {int am_flags; int /*<<< orphan*/  am_path; TYPE_1__* am_al; } ;
typedef  TYPE_3__ am_node ;
struct TYPE_13__ {int /*<<< orphan*/  d_uerr; } ;
struct TYPE_10__ {TYPE_2__* al_mnt; } ;

/* Variables and functions */
 int AMF_AUTOFS ; 
 int /*<<< orphan*/  AMQ_UMNT_FAILED ; 
 int /*<<< orphan*/  AMQ_UMNT_SIGNAL ; 
 int EBUSY ; 
 int ENOENT ; 
 int MFF_IS_AUTOFS ; 
 int MFF_UNMOUNTING ; 
 int MFF_WANTTIMO ; 
 int SIGTRAP ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_STATS ; 
 int /*<<< orphan*/  am_unmounted (TYPE_3__*) ; 
 TYPE_8__ amd_stats ; 
 int /*<<< orphan*/  amfs_program_ops ; 
 int /*<<< orphan*/  autofs_get_mp (TYPE_3__*) ; 
 int /*<<< orphan*/  autofs_umount_failed (TYPE_3__*) ; 
 int /*<<< orphan*/  get_mntfs_wchan (TYPE_2__*) ; 
 int /*<<< orphan*/  notify_child (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reschedule_timeout_mp () ; 
 int strerror (int) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_map_if_success(int rc, int term, opaque_t arg)
{
  am_node *mp = (am_node *) arg;
  mntfs *mf = mp->am_al->al_mnt;
  wchan_t wchan = get_mntfs_wchan(mf);

  /*
   * Not unmounting any more
   */
  mf->mf_flags &= ~MFF_UNMOUNTING;

  /*
   * If a timeout was deferred because the underlying filesystem
   * was busy then arrange for a timeout as soon as possible.
   */
  if (mf->mf_flags & MFF_WANTTIMO) {
    mf->mf_flags &= ~MFF_WANTTIMO;
    reschedule_timeout_mp();
  }
  if (term) {
    notify_child(mp, AMQ_UMNT_SIGNAL, 0, term);
    plog(XLOG_ERROR, "unmount for %s got signal %d", mp->am_path, term);
#if defined(DEBUG) && defined(SIGTRAP)
    /*
     * dbx likes to put a trap on exit().
     * Pretend it succeeded for now...
     */
    if (term == SIGTRAP) {
      am_unmounted(mp);
    }
#endif /* DEBUG */
#ifdef HAVE_FS_AUTOFS
    if (mp->am_flags & AMF_AUTOFS)
      autofs_umount_failed(mp);
#endif /* HAVE_FS_AUTOFS */
    amd_stats.d_uerr++;
  } else if (rc) {
    notify_child(mp, AMQ_UMNT_FAILED, rc, 0);
    if (mf->mf_ops == &amfs_program_ops || rc == EBUSY)
      plog(XLOG_STATS, "\"%s\" on %s still active", mp->am_path, mf->mf_mount);
    else
      plog(XLOG_ERROR, "%s: unmount: %s", mp->am_path, strerror(rc));
#ifdef HAVE_FS_AUTOFS
    if (rc != ENOENT) {
      if (mf->mf_flags & MFF_IS_AUTOFS)
        autofs_get_mp(mp);
      if (mp->am_flags & AMF_AUTOFS)
        autofs_umount_failed(mp);
    }
#endif /* HAVE_FS_AUTOFS */
    amd_stats.d_uerr++;
  } else {
    /*
     * am_unmounted() will call notify_child() appropriately.
     */
    am_unmounted(mp);
  }

  /*
   * Wakeup anything waiting for this unmount
   */
  wakeup(wchan);
}