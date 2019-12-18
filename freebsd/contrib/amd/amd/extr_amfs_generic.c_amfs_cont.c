#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct continuation {TYPE_5__* mp; int /*<<< orphan*/  al; } ;
typedef  scalar_t__ opaque_t ;
struct TYPE_16__ {int mf_flags; int mf_error; TYPE_2__* mf_ops; TYPE_1__* mf_server; } ;
typedef  TYPE_4__ mntfs ;
struct TYPE_17__ {scalar_t__ am_error; int /*<<< orphan*/  am_path; TYPE_3__* am_al; } ;
typedef  TYPE_5__ am_node ;
struct TYPE_15__ {TYPE_4__* al_mnt; } ;
struct TYPE_14__ {int /*<<< orphan*/  fs_type; } ;
struct TYPE_13__ {int fs_version; int /*<<< orphan*/  fs_proto; } ;
struct TYPE_12__ {int /*<<< orphan*/  d_merr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int MFF_ERROR ; 
 int MFF_IS_AUTOFS ; 
 int MFF_MOUNTED ; 
 int MFF_MOUNTING ; 
 int MFF_NFS_SCALEDOWN ; 
 int /*<<< orphan*/  STREQ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  am_mounted (TYPE_5__*) ; 
 TYPE_10__ amd_stats ; 
 int /*<<< orphan*/  amfs_bgmount (struct continuation*) ; 
 int /*<<< orphan*/  assign_error_mntfs (TYPE_5__*) ; 
 int /*<<< orphan*/  autofs_release_fh (TYPE_5__*) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free_continuation (struct continuation*) ; 
 int /*<<< orphan*/  get_mntfs_wchan (TYPE_4__*) ; 
 int /*<<< orphan*/  new_ttl (TYPE_5__*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  reschedule_timeout_mp () ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amfs_cont(int rc, int term, opaque_t arg)
{
  struct continuation *cp = (struct continuation *) arg;
  am_node *mp = cp->mp;
  mntfs *mf = mp->am_al->al_mnt;

  dlog("amfs_cont: '%s'", mp->am_path);

  /*
   * Definitely not trying to mount at the moment
   */
  mf->mf_flags &= ~MFF_MOUNTING;

  /*
   * While we are mounting - try to avoid race conditions
   */
  new_ttl(mp);

  /*
   * Wakeup anything waiting for this mount
   */
  wakeup(get_mntfs_wchan(mf));

  /*
   * Check for termination signal or exit status...
   */
  if (rc || term) {
#ifdef HAVE_FS_AUTOFS
    if (mf->mf_flags & MFF_IS_AUTOFS &&
	!(mf->mf_flags & MFF_MOUNTED))
      autofs_release_fh(mp);
#endif /* HAVE_FS_AUTOFS */

    if (term) {
      /*
       * Not sure what to do for an error code.
       */
      mf->mf_error = EIO;	/* XXX ? */
      mf->mf_flags |= MFF_ERROR;
      plog(XLOG_ERROR, "mount for %s got signal %d", mp->am_path, term);
    } else {
      /*
       * Check for exit status...
       */
#ifdef __linux__
      /*
       * HACK ALERT!
       *
       * On Linux (and maybe not only) it's possible to run
       * an amd which "knows" how to mount certain combinations
       * of nfs_proto/nfs_version which the kernel doesn't grok.
       * So if we got an EINVAL and we have a server that's not
       * using NFSv2/UDP, try again with NFSv2/UDP.
       *
       * Too bad that there is no way to dynamically determine
       * what combinations the _client_ supports, as opposed to
       * what the _server_ supports...
       */
      if (rc == EINVAL &&
	  mf->mf_server &&
	  (mf->mf_server->fs_version != 2 ||
	   !STREQ(mf->mf_server->fs_proto, "udp")))
	mf->mf_flags |= MFF_NFS_SCALEDOWN;
      else
#endif /* __linux__ */
      {
	mf->mf_error = rc;
	mf->mf_flags |= MFF_ERROR;
	errno = rc;		/* XXX */
	if (!STREQ(mp->am_al->al_mnt->mf_ops->fs_type, "linkx"))
	  plog(XLOG_ERROR, "%s: mount (amfs_cont): %m", mp->am_path);
      }
    }

    if (!(mf->mf_flags & MFF_NFS_SCALEDOWN)) {
      /*
       * If we get here then that attempt didn't work, so
       * move the info vector pointer along by one and
       * call the background mount routine again
       */
      amd_stats.d_merr++;
      cp->al++;
    }
    amfs_bgmount(cp);
    if (mp->am_error > 0)
      assign_error_mntfs(mp);
  } else {
    /*
     * The mount worked.
     */
    dlog("Mounting %s returned success", cp->mp->am_path);
    am_mounted(cp->mp);
    free_continuation(cp);
  }

  reschedule_timeout_mp();
}