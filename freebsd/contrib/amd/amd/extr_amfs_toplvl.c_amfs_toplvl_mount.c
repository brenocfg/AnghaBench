#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  toplvl_opts ;
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  preopts ;
typedef  int /*<<< orphan*/  opts ;
struct TYPE_10__ {int mf_flags; int /*<<< orphan*/  mf_info; TYPE_1__* mf_ops; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_11__ {int /*<<< orphan*/  am_autofs_fh; int /*<<< orphan*/  am_path; } ;
typedef  TYPE_3__ am_node ;
struct TYPE_12__ {scalar_t__* amfs_auto_timeo; scalar_t__* amfs_auto_retrans; scalar_t__ auto_attrcache; } ;
struct TYPE_9__ {int /*<<< orphan*/  fs_type; } ;

/* Variables and functions */
 size_t AMU_TYPE_TOPLVL ; 
 int ENOTDIR ; 
 int MFF_IS_AUTOFS ; 
 char* MNTTAB_OPT_IGNORE ; 
 char* MNTTAB_OPT_INTR ; 
 char* MNTTAB_OPT_NOAC ; 
 char* MNTTAB_OPT_NOLOCK ; 
 int /*<<< orphan*/  MNTTAB_OPT_PORT ; 
 int /*<<< orphan*/  MNTTAB_OPT_RETRANS ; 
 int /*<<< orphan*/  MNTTAB_OPT_RW ; 
 int /*<<< orphan*/  MNTTAB_OPT_TIMEO ; 
 int SIZEOF_OPTS ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int amfs_mount (TYPE_3__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  autofs_get_opts (char*,int,int /*<<< orphan*/ ) ; 
 int errno ; 
 TYPE_4__ gopt ; 
 int /*<<< orphan*/  nfs_port ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  set_auto_attrcache_timeout (char*,char*,int) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  xstrlcat (char*,char*,int) ; 

int
amfs_toplvl_mount(am_node *mp, mntfs *mf)
{
  struct stat stb;
  char opts[SIZEOF_OPTS], preopts[SIZEOF_OPTS], toplvl_opts[40];
  int error;

  /*
   * Mounting the automounter.
   * Make sure the mount directory exists, construct
   * the mount options and call the mount_amfs_toplvl routine.
   */

  if (stat(mp->am_path, &stb) < 0) {
    return errno;
  } else if ((stb.st_mode & S_IFMT) != S_IFDIR) {
    plog(XLOG_WARNING, "%s is not a directory", mp->am_path);
    return ENOTDIR;
  }

  /*
   * Construct some mount options:
   *
   * Tack on magic map=<mapname> option in mtab to emulate
   * SunOS automounter behavior.
   */

#ifdef HAVE_FS_AUTOFS
  if (mf->mf_flags & MFF_IS_AUTOFS) {
    autofs_get_opts(opts, sizeof(opts), mp->am_autofs_fh);
  } else
#endif /* HAVE_FS_AUTOFS */
  {
    preopts[0] = '\0';
#ifdef MNTTAB_OPT_INTR
    xstrlcat(preopts, MNTTAB_OPT_INTR, sizeof(preopts));
    xstrlcat(preopts, ",", sizeof(preopts));
#endif /* MNTTAB_OPT_INTR */
#ifdef MNTTAB_OPT_IGNORE
    xstrlcat(preopts, MNTTAB_OPT_IGNORE, sizeof(preopts));
    xstrlcat(preopts, ",", sizeof(preopts));
#endif /* MNTTAB_OPT_IGNORE */
    /* write most of the initial options + preopts */
    xsnprintf(opts, sizeof(opts), "%s%s,%s=%d,%s,map=%s",
	      preopts,
	      MNTTAB_OPT_RW,
	      MNTTAB_OPT_PORT, nfs_port,
	      mf->mf_ops->fs_type, mf->mf_info);

    /* process toplvl timeo/retrans options, if any */
    if (gopt.amfs_auto_timeo[AMU_TYPE_TOPLVL] > 0) {
      xsnprintf(toplvl_opts, sizeof(toplvl_opts), ",%s=%d",
		MNTTAB_OPT_TIMEO, gopt.amfs_auto_timeo[AMU_TYPE_TOPLVL]);
      xstrlcat(opts, toplvl_opts, sizeof(opts));
    }
    if (gopt.amfs_auto_retrans[AMU_TYPE_TOPLVL] > 0) {
      xsnprintf(toplvl_opts, sizeof(toplvl_opts), ",%s=%d",
		MNTTAB_OPT_RETRANS, gopt.amfs_auto_retrans[AMU_TYPE_TOPLVL]);
      xstrlcat(opts, toplvl_opts, sizeof(opts));
    }

#ifdef MNTTAB_OPT_NOLOCK
    xstrlcat(opts, ",", sizeof(opts));
    xstrlcat(opts, MNTTAB_OPT_NOLOCK, sizeof(opts));
#endif /* MNTTAB_OPT_NOLOCK */

#ifdef MNTTAB_OPT_NOAC
    if (gopt.auto_attrcache == 0) {
      xstrlcat(opts, ",", sizeof(opts));
      xstrlcat(opts, MNTTAB_OPT_NOAC, sizeof(opts));
    } else
#endif /* MNTTAB_OPT_NOAC */
      set_auto_attrcache_timeout(preopts, opts, sizeof(preopts));
  }

  /* now do the mount */
  error = amfs_mount(mp, mf, opts);
  if (error) {
    errno = error;
    plog(XLOG_FATAL, "amfs_toplvl_mount: amfs_mount failed: %m");
    return error;
  }
  return 0;
}