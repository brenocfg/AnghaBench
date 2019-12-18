#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  transp_timeo_opts ;
typedef  int /*<<< orphan*/  transp_retrans_opts ;
typedef  int /*<<< orphan*/  nfs_args_t ;
typedef  int /*<<< orphan*/  nfs4_args_t ;
struct TYPE_15__ {int mf_flags; scalar_t__* mf_mopts; scalar_t__* mf_remopts; TYPE_4__* mf_server; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_16__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; void* mnt_type; } ;
typedef  TYPE_3__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  host ;
struct TYPE_17__ {scalar_t__ fs_version; char* fs_proto; TYPE_10__* fs_ip; } ;
typedef  TYPE_4__ fserver ;
typedef  int /*<<< orphan*/  am_nfs_handle_t ;
struct TYPE_18__ {scalar_t__* amfs_auto_timeo; scalar_t__* amfs_auto_retrans; } ;
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_13__ {TYPE_1__ sin_addr; } ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int AMU_TYPE_NONE ; 
 int AMU_TYPE_TCP ; 
 int AMU_TYPE_UDP ; 
 int /*<<< orphan*/  D_TRACE ; 
 int ENOENT ; 
 int EPERM ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int MFF_ON_AUTOFS ; 
 int /*<<< orphan*/  MNTTAB_OPT_RETRANS ; 
 int /*<<< orphan*/  MNTTAB_OPT_RETRY ; 
 int /*<<< orphan*/  MNTTAB_OPT_TIMEO ; 
 void* MNTTAB_TYPE_NFS ; 
 void* MNTTAB_TYPE_NFS3 ; 
 void* MNTTAB_TYPE_NFS4 ; 
 int /*<<< orphan*/  MOUNT_TYPE_NFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_NFS3 ; 
 int /*<<< orphan*/  MOUNT_TYPE_NFS4 ; 
 scalar_t__ NFS_VERSION3 ; 
 scalar_t__ NFS_VERSION4 ; 
 scalar_t__ STREQ (char*,char*) ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int autofs_compute_mount_flags (TYPE_3__*) ; 
 int compute_mount_flags (TYPE_3__*) ; 
 int /*<<< orphan*/  compute_nfs_args (void*,TYPE_3__*,int,int /*<<< orphan*/ *,TYPE_10__*,scalar_t__,char*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  discard_nfs_args (void*,scalar_t__) ; 
 TYPE_8__ gopt ; 
 int hasmntval (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  islocalnet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_3__*,int,void*,int,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_nfs_args (void*,scalar_t__) ; 
 char* str3cat (char*,char*,char*,scalar_t__*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int) ; 

int
mount_nfs_fh(am_nfs_handle_t *fhp, char *mntdir, char *fs_name, mntfs *mf)
{
  MTYPE_TYPE type;
  char *colon;
  char *xopts=NULL, transp_timeo_opts[40], transp_retrans_opts[40];
  char host[MAXHOSTNAMELEN + MAXPATHLEN + 2];
  fserver *fs = mf->mf_server;
  u_long nfs_version = fs->fs_version;
  char *nfs_proto = fs->fs_proto; /* "tcp" or "udp" */
  int on_autofs = mf->mf_flags & MFF_ON_AUTOFS;
  int error;
  int genflags;
  int retry;
  int proto = AMU_TYPE_NONE;
  mntent_t mnt;
  void *argsp;
  nfs_args_t nfs_args;
#ifdef HAVE_FS_NFS4
  nfs4_args_t nfs4_args;
#endif /* HAVE_FS_NFS4 */

  /*
   * Extract HOST name to give to kernel.
   * Some systems like osf1/aix3/bsd44 variants may need old code
   * for NFS_ARGS_NEEDS_PATH.
   */
  if (!(colon = strchr(fs_name, ':')))
    return ENOENT;
#ifdef MOUNT_TABLE_ON_FILE
  *colon = '\0';
#endif /* MOUNT_TABLE_ON_FILE */
  xstrlcpy(host, fs_name, sizeof(host));
#ifdef MOUNT_TABLE_ON_FILE
  *colon = ':';
#endif /* MOUNT_TABLE_ON_FILE */
#ifdef MAXHOSTNAMELEN
  /* most kernels have a name length restriction */
  if (strlen(host) >= MAXHOSTNAMELEN)
    xstrlcpy(host + MAXHOSTNAMELEN - 3, "..",
	     sizeof(host) - MAXHOSTNAMELEN + 3);
#endif /* MAXHOSTNAMELEN */

  /*
   * Create option=VAL for udp/tcp specific timeouts and retrans values, but
   * only if these options were specified.
   */

  transp_timeo_opts[0] = transp_retrans_opts[0] = '\0';	/* initialize */
  if (STREQ(nfs_proto, "udp"))
    proto = AMU_TYPE_UDP;
  else if (STREQ(nfs_proto, "tcp"))
    proto = AMU_TYPE_TCP;
  if (proto != AMU_TYPE_NONE) {
    if (gopt.amfs_auto_timeo[proto] > 0)
      xsnprintf(transp_timeo_opts, sizeof(transp_timeo_opts), "%s=%d,",
		MNTTAB_OPT_TIMEO, gopt.amfs_auto_timeo[proto]);
    if (gopt.amfs_auto_retrans[proto] > 0)
      xsnprintf(transp_retrans_opts, sizeof(transp_retrans_opts), "%s=%d,",
		MNTTAB_OPT_RETRANS, gopt.amfs_auto_retrans[proto]);
  }

  if (mf->mf_remopts && *mf->mf_remopts &&
      !islocalnet(fs->fs_ip->sin_addr.s_addr)) {
    plog(XLOG_INFO, "Using remopts=\"%s\"", mf->mf_remopts);
    /* use transp_opts first, so map-specific opts will override */
    xopts = str3cat(xopts, transp_timeo_opts, transp_retrans_opts, mf->mf_remopts);
  } else {
    /* use transp_opts first, so map-specific opts will override */
    xopts = str3cat(xopts, transp_timeo_opts, transp_retrans_opts, mf->mf_mopts);
  }

  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = fs_name;
  mnt.mnt_opts = xopts;

  /*
   * Set mount types accordingly
   */
#ifdef HAVE_FS_NFS3
  if (nfs_version == NFS_VERSION3) {
    type = MOUNT_TYPE_NFS3;
    /*
     * Systems that include the mount table "vers" option generally do not
     * set the mnttab entry to "nfs3", but to "nfs" and then they set
     * "vers=3".  Setting it to "nfs3" works, but it may break some things
     * like "df -t nfs" and the "quota" program (esp. on Solaris and Irix).
     * So on those systems, set it to "nfs".
     * Note: MNTTAB_OPT_VERS is always set for NFS3 (see am_compat.h).
     */
    argsp = &nfs_args;
# if defined(MNTTAB_OPT_VERS) && defined(MOUNT_TABLE_ON_FILE)
    mnt.mnt_type = MNTTAB_TYPE_NFS;
# else /* defined(MNTTAB_OPT_VERS) && defined(MOUNT_TABLE_ON_FILE) */
    mnt.mnt_type = MNTTAB_TYPE_NFS3;
# endif /* defined(MNTTAB_OPT_VERS) && defined(MOUNT_TABLE_ON_FILE) */
# ifdef HAVE_FS_NFS4
  } else if (nfs_version == NFS_VERSION4) {
    argsp = &nfs4_args;
    type = MOUNT_TYPE_NFS4;
    mnt.mnt_type = MNTTAB_TYPE_NFS4;
# endif /* HAVE_FS_NFS4 */
  } else
#endif /* HAVE_FS_NFS3 */
  {
    argsp = &nfs_args;
    type = MOUNT_TYPE_NFS;
    mnt.mnt_type = MNTTAB_TYPE_NFS;
  }
  plog(XLOG_INFO, "mount_nfs_fh: NFS version %d", (int) nfs_version);
  plog(XLOG_INFO, "mount_nfs_fh: using NFS transport %s", nfs_proto);

  retry = hasmntval(&mnt, MNTTAB_OPT_RETRY);
  if (retry <= 0)
    retry = 1;			/* XXX */

  genflags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    genflags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */

   /* setup the many fields and flags within nfs_args */
   compute_nfs_args(argsp,
		    &mnt,
		    genflags,
		    NULL,	/* struct netconfig *nfsncp */
		    fs->fs_ip,
		    nfs_version,
		    nfs_proto,
		    fhp,
		    host,
		    fs_name);

  /* finally call the mounting function */
  if (amuDebug(D_TRACE)) {
    print_nfs_args(argsp, nfs_version);
    plog(XLOG_DEBUG, "Generic mount flags 0x%x used for NFS mount", genflags);
  }
  error = mount_fs(&mnt, genflags, argsp, retry, type,
		   nfs_version, nfs_proto, mnttab_file_name, on_autofs);
  XFREE(mnt.mnt_opts);
  discard_nfs_args(argsp, nfs_version);

#ifdef HAVE_FS_NFS4
# ifndef NO_FALLBACK
  /*
   * If we are using a v4 file handle, we try a v3 if we get back:
   * 	ENOENT: NFS v4 has a different export list than v3
   * 	EPERM: Kernels <= 2.6.18 return that, instead of ENOENT
   */
  if ((error == ENOENT || error == EPERM) && nfs_version == NFS_VERSION4) {
    plog(XLOG_DEBUG, "Could not find NFS 4 mount, trying again with NFS 3");
    fs->fs_version = NFS_VERSION3;
    error = mount_nfs_fh(fhp, mntdir, fs_name, mf);
    if (error)
      fs->fs_version = NFS_VERSION4;
  }
# endif /* NO_FALLBACK */
#endif /* HAVE_FS_NFS4 */

  return error;
}