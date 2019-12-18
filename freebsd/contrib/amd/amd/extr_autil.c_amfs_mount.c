#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_long ;
struct sockaddr_in {char* mnt_dir; char* mnt_opts; char* mnt_type; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  mnt_fsname; } ;
typedef  int /*<<< orphan*/  sin ;
struct TYPE_11__ {int /*<<< orphan*/  knconf; int /*<<< orphan*/ * addr; } ;
typedef  TYPE_1__ nfs_args_t ;
struct TYPE_12__ {int mf_flags; char* mf_mount; } ;
typedef  TYPE_2__ mntfs ;
typedef  struct sockaddr_in mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  fs_hostname ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_13__ {int am_path; scalar_t__ am_autofs_fh; } ;
typedef  TYPE_3__ am_node ;
typedef  int /*<<< orphan*/  am_nfs_handle_t ;
struct TYPE_15__ {int flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  xp_ltaddr; } ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int AMU_UMOUNT_DETACH ; 
 int AMU_UMOUNT_FORCE ; 
 int CFM_FORCED_UNMOUNTS ; 
 int /*<<< orphan*/  D_TRACE ; 
 int EINVAL ; 
#define  EIO 129 
#define  ESTALE 128 
 char* HIDE_MOUNT_TYPE ; 
 int HOSTNAMESZ ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int MFF_IS_AUTOFS ; 
 int MFF_ON_AUTOFS ; 
 int /*<<< orphan*/  MNTTAB_OPT_PORT ; 
 int /*<<< orphan*/  MNTTAB_OPT_RETRY ; 
 int /*<<< orphan*/  MOUNT_TYPE_AUTOFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_NFS ; 
 int UMOUNT_FS (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  am_get_hostname () ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int autofs_compute_mount_flags (struct sockaddr_in*) ; 
 int compute_automounter_mount_flags (struct sockaddr_in*) ; 
 int /*<<< orphan*/  compute_automounter_nfs_args (TYPE_1__*,struct sockaddr_in*) ; 
 int compute_mount_flags (struct sockaddr_in*) ; 
 int /*<<< orphan*/  compute_nfs_args (TYPE_1__*,struct sockaddr_in*,int,int /*<<< orphan*/ *,struct sockaddr_in*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free_knetconfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nfs_dispatcher_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_root_nfs_fh (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_server_pid () ; 
 TYPE_6__ gopt ; 
 int hasmntval (struct sockaddr_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (struct sockaddr_in*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  myipaddr ; 
 int /*<<< orphan*/  nfs_dispatcher ; 
 int /*<<< orphan*/ * nfsncp ; 
 TYPE_5__* nfsxprt ; 
 int /*<<< orphan*/  pid_fsname ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_nfs_args (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int) ; 

int
amfs_mount(am_node *mp, mntfs *mf, char *opts)
{
  char fs_hostname[MAXHOSTNAMELEN + MAXPATHLEN + 1];
  int retry, error = 0, genflags;
  int on_autofs = mf->mf_flags & MFF_ON_AUTOFS;
  char *dir = mf->mf_mount;
  mntent_t mnt;
  MTYPE_TYPE type;
  int forced_unmount = 0;	/* are we using forced unmounts? */
  u_long nfs_version = get_nfs_dispatcher_version(nfs_dispatcher);

  memset(&mnt, 0, sizeof(mnt));
  mnt.mnt_dir = dir;
  mnt.mnt_fsname = pid_fsname;
  mnt.mnt_opts = opts;

#ifdef HAVE_FS_AUTOFS
  if (mf->mf_flags & MFF_IS_AUTOFS) {
    type = MOUNT_TYPE_AUTOFS;
    /*
     * Make sure that amd's top-level autofs mounts are hidden by default
     * from df.
     * XXX: It works ok on Linux, might not work on other systems.
     */
    mnt.mnt_type = "autofs";
  } else
#endif /* HAVE_FS_AUTOFS */
  {
    type = MOUNT_TYPE_NFS;
    /*
     * Make sure that amd's top-level NFS mounts are hidden by default
     * from df.
     * If they don't appear to support the either the "ignore" mnttab
     * option entry, or the "auto" one, set the mount type to "nfs".
     */
    mnt.mnt_type = HIDE_MOUNT_TYPE;
  }

  retry = hasmntval(&mnt, MNTTAB_OPT_RETRY);
  if (retry <= 0)
    retry = 2;			/* XXX: default to 2 retries */

  /*
   * SET MOUNT ARGS
   */

  /*
   * Make a ``hostname'' string for the kernel
   */
  xsnprintf(fs_hostname, sizeof(fs_hostname), "pid%ld@%s:%s",
	    get_server_pid(), am_get_hostname(), dir);
  /*
   * Most kernels have a name length restriction (64 bytes)...
   */
  if (strlen(fs_hostname) >= MAXHOSTNAMELEN)
    xstrlcpy(fs_hostname + MAXHOSTNAMELEN - 3, "..",
	     sizeof(fs_hostname) - MAXHOSTNAMELEN + 3);
#ifdef HOSTNAMESZ
  /*
   * ... and some of these restrictions are 32 bytes (HOSTNAMESZ)
   * If you need to get the definition for HOSTNAMESZ found, you may
   * add the proper header file to the conf/nfs_prot/nfs_prot_*.h file.
   */
  if (strlen(fs_hostname) >= HOSTNAMESZ)
    xstrlcpy(fs_hostname + HOSTNAMESZ - 3, "..",
	     sizeof(fs_hostname) - HOSTNAMESZ + 3);
#endif /* HOSTNAMESZ */

  /*
   * Finally we can compute the mount genflags set above,
   * and add any automounter specific flags.
   */
  genflags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    genflags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */
  genflags |= compute_automounter_mount_flags(&mnt);

again:
  if (!(mf->mf_flags & MFF_IS_AUTOFS)) {
    nfs_args_t nfs_args;
    am_nfs_handle_t *fhp, anh;
#ifndef HAVE_TRANSPORT_TYPE_TLI
    u_short port;
    struct sockaddr_in sin;
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

    /*
     * get fhandle of remote path for automount point
     */
    fhp = get_root_nfs_fh(dir, &anh);
    if (!fhp) {
      plog(XLOG_FATAL, "Can't find root file handle for %s", dir);
      return EINVAL;
    }

#ifndef HAVE_TRANSPORT_TYPE_TLI
    /*
     * Create sockaddr to point to the local machine.
     */
    memset(&sin, 0, sizeof(sin));
    /* as per POSIX, sin_len need not be set (used internally by kernel) */
    sin.sin_family = AF_INET;
    sin.sin_addr = myipaddr;
    port = hasmntval(&mnt, MNTTAB_OPT_PORT);
    if (port) {
      sin.sin_port = htons(port);
    } else {
      plog(XLOG_ERROR, "no port number specified for %s", dir);
      return EINVAL;
    }
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

    /* setup the many fields and flags within nfs_args */
#ifdef HAVE_TRANSPORT_TYPE_TLI
    compute_nfs_args(&nfs_args,
		     &mnt,
		     genflags,
		     nfsncp,
		     NULL,	/* remote host IP addr is set below */
		     nfs_version,
		     "udp",
		     fhp,
		     fs_hostname,
		     pid_fsname);
    /*
     * IMPORTANT: set the correct IP address AFTERWARDS.  It cannot
     * be done using the normal mechanism of compute_nfs_args(), because
     * that one will allocate a new address and use NFS_SA_DREF() to copy
     * parts to it, while assuming that the ip_addr passed is always
     * a "struct sockaddr_in".  That assumption is incorrect on TLI systems,
     * because they define a special macro HOST_SELF which is DIFFERENT
     * than localhost (127.0.0.1)!
     */
    nfs_args.addr = &nfsxprt->xp_ltaddr;
#else /* not HAVE_TRANSPORT_TYPE_TLI */
    compute_nfs_args(&nfs_args,
		     &mnt,
		     genflags,
		     NULL,
		     &sin,
		     nfs_version,
		     "udp",
		     fhp,
		     fs_hostname,
		     pid_fsname);
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

    /*************************************************************************
     * NOTE: while compute_nfs_args() works ok for regular NFS mounts	     *
     * the toplvl one is not quite regular, and so some options must be      *
     * corrected by hand more carefully, *after* compute_nfs_args() runs.    *
     *************************************************************************/
    compute_automounter_nfs_args(&nfs_args, &mnt);

    if (amuDebug(D_TRACE)) {
      print_nfs_args(&nfs_args, 0);
      plog(XLOG_DEBUG, "Generic mount flags 0x%x", genflags);
    }

    /* This is it!  Here we try to mount amd on its mount points */
    error = mount_fs(&mnt, genflags, (caddr_t) &nfs_args,
		     retry, type, 0, NULL, mnttab_file_name, on_autofs);

#ifdef HAVE_TRANSPORT_TYPE_TLI
    free_knetconfig(nfs_args.knconf);
    /*
     * local automounter mounts do not allocate a special address, so
     * no need to XFREE(nfs_args.addr) under TLI.
     */
#endif /* HAVE_TRANSPORT_TYPE_TLI */

#ifdef HAVE_FS_AUTOFS
  } else {
    /* This is it!  Here we try to mount amd on its mount points */
    error = mount_fs(&mnt, genflags, (caddr_t) mp->am_autofs_fh,
		     retry, type, 0, NULL, mnttab_file_name, on_autofs);
#endif /* HAVE_FS_AUTOFS */
  }
  if (error == 0 || forced_unmount)
     return error;

  /*
   * If user wants forced/lazy unmount semantics, then try it iff the
   * current mount failed with EIO or ESTALE.
   */
  if (gopt.flags & CFM_FORCED_UNMOUNTS) {
    switch (errno) {
    case ESTALE:
    case EIO:
      forced_unmount = errno;
      plog(XLOG_WARNING, "Mount %s failed (%m); force unmount.", mp->am_path);
      if ((error = UMOUNT_FS(mp->am_path, mnttab_file_name,
			     AMU_UMOUNT_FORCE | AMU_UMOUNT_DETACH)) < 0) {
	plog(XLOG_WARNING, "Forced umount %s failed: %m.", mp->am_path);
	errno = forced_unmount;
      } else
	goto again;
    default:
      break;
    }
  }

  return error;
}