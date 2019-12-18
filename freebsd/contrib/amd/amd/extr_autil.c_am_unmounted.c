#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
struct TYPE_20__ {int mf_flags; int mf_refc; char* mf_mount; TYPE_15__* mf_ops; } ;
typedef  TYPE_3__ mntfs ;
struct TYPE_18__ {scalar_t__ na_type; int /*<<< orphan*/  na_mtime; int /*<<< orphan*/  na_nlink; } ;
struct TYPE_21__ {char* am_name; int am_flags; int* am_fd; int /*<<< orphan*/  am_alarray; TYPE_2__* am_al; struct TYPE_21__* am_parent; TYPE_1__ am_fattr; scalar_t__ am_link; } ;
typedef  TYPE_4__ am_node ;
struct TYPE_19__ {TYPE_3__* al_mnt; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* mount_child ) (TYPE_4__*,int*) ;TYPE_4__* (* lookup_child ) (TYPE_4__*,char*,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* umount_fs ) (TYPE_4__*,TYPE_3__*) ;int /*<<< orphan*/  (* umounted ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int AMF_AUTOFS ; 
 int AMF_REMOUNT ; 
 int /*<<< orphan*/  AMQ_UMNT_FAILED ; 
 int /*<<< orphan*/  AMQ_UMNT_OK ; 
 int /*<<< orphan*/  EBUSY ; 
 int MFF_IS_AUTOFS ; 
 int MFF_MKMNT ; 
 scalar_t__ NFDIR ; 
 int /*<<< orphan*/  VLOOK_CREATE ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 TYPE_15__ amfs_link_ops ; 
 int /*<<< orphan*/  autofs_release_fh (TYPE_4__*) ; 
 int /*<<< orphan*/  autofs_umount_succeeded (TYPE_4__*) ; 
 int /*<<< orphan*/  clocktime (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  foreground ; 
 int /*<<< orphan*/  free_map (TYPE_4__*) ; 
 int /*<<< orphan*/  notify_child (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  rmdirs (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_3__*) ; 
 TYPE_4__* stub3 (TYPE_4__*,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int*) ; 
 char* xstrdup (char*) ; 

void
am_unmounted(am_node *mp)
{
  mntfs *mf = mp->am_al->al_mnt;

  if (!foreground) {		/* firewall - should never happen */
    /*
     * This is a coding error.  Make sure we hear about it!
     */
    plog(XLOG_FATAL, "am_unmounted: illegal use in background (%s)",
	mp->am_name);
    notify_child(mp, AMQ_UMNT_OK, 0, 0);	/* XXX - be safe? */
    return;
  }

  /*
   * Do unmounted callback
   */
  if (mf->mf_ops->umounted)
    mf->mf_ops->umounted(mf);

  /*
   * This is ugly, but essentially unavoidable.
   * Sublinks must be treated separately as type==link
   * when the base type is different.
   */
  if (mp->am_link && mf->mf_ops != &amfs_link_ops)
    amfs_link_ops.umount_fs(mp, mf);

#ifdef HAVE_FS_AUTOFS
  if (mf->mf_flags & MFF_IS_AUTOFS)
    autofs_release_fh(mp);
  if (mp->am_flags & AMF_AUTOFS)
    autofs_umount_succeeded(mp);
#endif /* HAVE_FS_AUTOFS */

  /*
   * Clean up any directories that were made
   *
   * If we remove the mount point of a pending mount, any queued access
   * to it will fail. So don't do it in that case.
   * Also don't do it if the refcount is > 1.
   */
  if (mf->mf_flags & MFF_MKMNT &&
      mf->mf_refc == 1 &&
      !(mp->am_flags & AMF_REMOUNT)) {
    plog(XLOG_INFO, "removing mountpoint directory '%s'", mf->mf_mount);
    rmdirs(mf->mf_mount);
    mf->mf_flags &= ~MFF_MKMNT;
  }

  /*
   * If this is a pseudo-directory then adjust the link count
   * in the parent
   */
  if (mp->am_parent && mp->am_fattr.na_type == NFDIR)
    --mp->am_parent->am_fattr.na_nlink;

  /*
   * Update mtime of parent node
   */
  if (mp->am_parent && mp->am_parent->am_al->al_mnt)
    clocktime(&mp->am_parent->am_fattr.na_mtime);

  if (mp->am_parent && (mp->am_flags & AMF_REMOUNT)) {
    char *fname = xstrdup(mp->am_name);
    am_node *mp_parent = mp->am_parent;
    mntfs *mf_parent = mp_parent->am_al->al_mnt;
    am_node fake_mp;
    int error = 0;

    /*
     * We need to use notify_child() after free_map(), so save enough
     * to do that in fake_mp.
     */
    fake_mp.am_fd[1] = mp->am_fd[1];
    mp->am_fd[1] = -1;

    free_map(mp);
    plog(XLOG_INFO, "am_unmounted: remounting %s", fname);
    mp = mf_parent->mf_ops->lookup_child(mp_parent, fname, &error, VLOOK_CREATE);
    if (mp && error < 0)
      (void)mf_parent->mf_ops->mount_child(mp, &error);
    if (error > 0) {
      errno = error;
      plog(XLOG_ERROR, "am_unmounted: could not remount %s: %m", fname);
      notify_child(&fake_mp, AMQ_UMNT_OK, 0, 0);
    } else {
      notify_child(&fake_mp, AMQ_UMNT_FAILED, EBUSY, 0);
    }
    XFREE(fname);
  } else {
    /*
     * We have a race here.
     * If this node has a pending mount and amd is going down (unmounting
     * everything in the process), then we could potentially free it here
     * while a struct continuation still has a reference to it. So when
     * amfs_cont is called, it blows up.
     * We avoid the race by refusing to free any nodes that have
     * pending mounts (defined as having a non-NULL am_alarray).
     */
    notify_child(mp, AMQ_UMNT_OK, 0, 0);	/* do this regardless */
    if (!mp->am_alarray)
      free_map(mp);
  }
}