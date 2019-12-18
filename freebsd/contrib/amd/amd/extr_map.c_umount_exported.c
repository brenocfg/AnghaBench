#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opaque_t ;
struct TYPE_10__ {int mf_flags; int mf_fsflags; int /*<<< orphan*/  mf_mount; TYPE_1__* mf_server; } ;
typedef  TYPE_3__ mntfs ;
struct TYPE_11__ {int am_flags; int am_timeo; scalar_t__ am_timeo_w; scalar_t__ am_ttl; TYPE_2__* am_al; scalar_t__ am_parent; int /*<<< orphan*/  am_fattr; scalar_t__ am_child; } ;
typedef  TYPE_4__ am_node ;
struct TYPE_12__ {int flags; } ;
struct TYPE_9__ {TYPE_3__* al_mnt; } ;
struct TYPE_8__ {int fs_flags; } ;

/* Variables and functions */
 int AMF_AUTOFS ; 
 int AMF_NOTIMEOUT ; 
 int AMF_ROOT ; 
 int CFM_UNMOUNT_ON_EXIT ; 
 int FSF_DOWN ; 
 int FSF_VALID ; 
 int FS_DIRECTORY ; 
 int MFF_MKMNT ; 
 int MFF_MOUNTED ; 
 int MFF_RESTART ; 
 int MFF_RSTKEEP ; 
 int MFF_UNMOUNTING ; 
 int /*<<< orphan*/  NFDIR ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  am_unmounted (TYPE_4__*) ; 
 TYPE_4__** exported_ap ; 
 TYPE_5__ gopt ; 
 scalar_t__ immediate_abort ; 
 int last_used_map ; 
 int /*<<< orphan*/  mk_fattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmount_mp (int /*<<< orphan*/ ) ; 

void
umount_exported(void)
{
  int i, work_done;

  do {
    work_done = 0;

    for (i = last_used_map; i >= 0; --i) {
      am_node *mp = exported_ap[i];
      mntfs *mf;

      if (!mp)
	continue;

      /*
       * Wait for children to be removed first
       */
      if (mp->am_child)
	continue;

      mf = mp->am_al->al_mnt;
      if (mf->mf_flags & MFF_UNMOUNTING) {
	/*
	 * If this node is being unmounted then just ignore it.  However,
	 * this could prevent amd from finishing if the unmount gets blocked
	 * since the am_node will never be free'd.  am_unmounted needs
	 * telling about this possibility. - XXX
	 */
	continue;
      }

      if (!(mf->mf_fsflags & FS_DIRECTORY))
	/*
	 * When shutting down this had better
	 * look like a directory, otherwise it
	 * can't be unmounted!
	 */
	mk_fattr(&mp->am_fattr, NFDIR);

      if ((--immediate_abort < 0 &&
	   !(mp->am_flags & AMF_ROOT) && mp->am_parent) ||
	  (mf->mf_flags & MFF_RESTART)) {

	work_done++;

	/*
	 * Just throw this node away without bothering to unmount it.  If
	 * the server is not known to be up then don't discard the mounted
	 * on directory or Amd might hang...
	 */
	if (mf->mf_server &&
	    (mf->mf_server->fs_flags & (FSF_DOWN | FSF_VALID)) != FSF_VALID)
	  mf->mf_flags &= ~MFF_MKMNT;
	if (gopt.flags & CFM_UNMOUNT_ON_EXIT || mp->am_flags & AMF_AUTOFS) {
	  plog(XLOG_INFO, "on-exit attempt to unmount %s", mf->mf_mount);
	  /*
	   * use unmount_mp, not unmount_node, so that unmounts be
	   * backgrounded as needed.
	   */
	  unmount_mp((opaque_t) mp);
	} else {
	  am_unmounted(mp);
	}
	if (!(mf->mf_flags & (MFF_UNMOUNTING|MFF_MOUNTED)))
	  exported_ap[i] = NULL;
      } else {
	/*
	 * Any other node gets forcibly timed out.
	 */
	mp->am_flags &= ~AMF_NOTIMEOUT;
	mp->am_al->al_mnt->mf_flags &= ~MFF_RSTKEEP;
	mp->am_ttl = 0;
	mp->am_timeo = 1;
	mp->am_timeo_w = 0;
      }
    }
  } while (work_done);
}