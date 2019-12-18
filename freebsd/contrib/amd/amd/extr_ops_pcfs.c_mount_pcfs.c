#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
typedef  int u_int ;
struct passwd {void* pw_uid; } ;
struct group {void* gr_gid; } ;
struct TYPE_8__ {char* fspec; int mask; int dirmask; scalar_t__ dsttime; scalar_t__ secondswest; void* gid; void* uid; } ;
typedef  TYPE_1__ pcfs_args_t ;
typedef  int /*<<< orphan*/  pcfs_args ;
struct TYPE_9__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; int /*<<< orphan*/  mnt_type; } ;
typedef  TYPE_2__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D_TRACE ; 
 int /*<<< orphan*/  MNTTAB_OPT_DIRMASK ; 
 int /*<<< orphan*/  MNTTAB_OPT_GROUP ; 
 int /*<<< orphan*/  MNTTAB_OPT_MASK ; 
 int /*<<< orphan*/  MNTTAB_OPT_USER ; 
 int /*<<< orphan*/  MNTTAB_TYPE_PCFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_PCFS ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 void* atoi (char*) ; 
 int autofs_compute_mount_flags (TYPE_2__*) ; 
 int compute_mount_flags (TYPE_2__*) ; 
 struct group* getgrnam (char*) ; 
 struct passwd* getpwnam (char*) ; 
 char* hasmntstr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int hasmntval (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
mount_pcfs(char *mntdir, char *fs_name, char *opts, int on_autofs)
{
  pcfs_args_t pcfs_args;
  mntent_t mnt;
  int flags;
#if defined(HAVE_PCFS_ARGS_T_MASK) || defined(HAVE_PCFS_ARGS_T_DIRMASK)
  int mask;
#endif /* defined(HAVE_PCFS_ARGS_T_MASK) || defined(HAVE_PCFS_ARGS_T_DIRMASK) */
#if defined(HAVE_PCFS_ARGS_T_UID) || defined(HAVE_PCFS_ARGS_T_UID)
  char *str;
#endif /* defined(HAVE_PCFS_ARGS_T_UID) || defined(HAVE_PCFS_ARGS_T_UID) */

  /*
   * Figure out the name of the file system type.
   */
  MTYPE_TYPE type = MOUNT_TYPE_PCFS;

  memset((voidp) &pcfs_args, 0, sizeof(pcfs_args)); /* Paranoid */

  /*
   * Fill in the mount structure
   */
  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = fs_name;
  mnt.mnt_type = MNTTAB_TYPE_PCFS;
  mnt.mnt_opts = opts;

  flags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    flags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */
  if (amuDebug(D_TRACE))
    plog(XLOG_DEBUG, "mount_pcfs: flags=0x%x", (u_int) flags);

#ifdef HAVE_PCFS_ARGS_T_FSPEC
  pcfs_args.fspec = fs_name;
#endif /* HAVE_PCFS_ARGS_T_FSPEC */

#ifdef HAVE_PCFS_ARGS_T_MASK
  pcfs_args.mask = 0777;	/* this may be the msdos file modes */
  if ((mask = hasmntval(&mnt, MNTTAB_OPT_MASK)) > 0)
    pcfs_args.mask = mask;
  if (amuDebug(D_TRACE))
    plog(XLOG_DEBUG, "mount_pcfs: mask=%o (octal)", (u_int) pcfs_args.mask);
#endif /* HAVE_PCFS_ARGS_T_MASK */

#ifdef HAVE_PCFS_ARGS_T_DIRMASK
  pcfs_args.dirmask = 0777;    /* this may be the msdos dir modes */
  if ((mask = hasmntval(&mnt, MNTTAB_OPT_DIRMASK)) > 0)
    pcfs_args.dirmask = mask;
  if (amuDebug(D_TRACE))
    plog(XLOG_DEBUG, "mount_pcfs: dirmask=%o (octal)", (u_int) pcfs_args.dirmask);
#endif /* HAVE_PCFS_ARGS_T_DIRMASK */

#ifdef HAVE_PCFS_ARGS_T_UID
  pcfs_args.uid = 0;		/* default to root */
  if ((str = hasmntstr(&mnt, MNTTAB_OPT_USER)) != NULL) {
    struct passwd *pw;
    if ((pw = getpwnam(str)) != NULL)
      pcfs_args.uid = pw->pw_uid;
    else		 /* maybe used passed a UID number, not user name */
      pcfs_args.uid = atoi(str); /* atoi returns '0' if it failed */
    XFREE(str);
  }
  if (amuDebug(D_TRACE))
    plog(XLOG_DEBUG, "mount_pcfs: uid=%d", (int) pcfs_args.uid);
#endif /* HAVE_PCFS_ARGS_T_UID */

#ifdef HAVE_PCFS_ARGS_T_GID
  pcfs_args.gid = 0;		/* default to wheel/root group */
  if ((str = hasmntstr(&mnt, MNTTAB_OPT_GROUP)) != NULL) {
    struct group *gr;
    if ((gr = getgrnam(str)) != NULL)
      pcfs_args.gid = gr->gr_gid;
    else		/* maybe used passed a GID number, not group name */
      pcfs_args.gid = atoi(str); /* atoi returns '0' if it failed */
    XFREE(str);
  }
  if (amuDebug(D_TRACE))
    plog(XLOG_DEBUG, "mount_pcfs: gid=%d", (int) pcfs_args.gid);
#endif /* HAVE_PCFS_ARGS_T_GID */

#ifdef HAVE_PCFS_ARGS_T_SECONDSWEST
  pcfs_args.secondswest = 0;	/* XXX: fill in correct values */
#endif /* HAVE_PCFS_ARGS_T_SECONDSWEST */
#ifdef HAVE_PCFS_ARGS_T_DSTTIME
  pcfs_args.dsttime = 0;	/* XXX: fill in correct values */
#endif /* HAVE_PCFS_ARGS_T_DSTTIME */

  /*
   * Call generic mount routine
   */
  return mount_fs(&mnt, flags, (caddr_t) & pcfs_args, 0, type, 0, NULL, mnttab_file_name, on_autofs);
}