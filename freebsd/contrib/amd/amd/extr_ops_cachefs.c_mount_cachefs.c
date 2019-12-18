#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char* voidp ;
struct TYPE_8__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; int /*<<< orphan*/  mnt_type; } ;
typedef  TYPE_2__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_7__ {int opt_flags; int /*<<< orphan*/  opt_fgsize; int /*<<< orphan*/  opt_popsize; } ;
struct TYPE_9__ {char* cfs_fsid; char* cfs_cacheid; char* cfs_cachedir; char* cfs_backfs; scalar_t__ cfs_acdirmax; scalar_t__ cfs_acdirmin; scalar_t__ cfs_acregmax; scalar_t__ cfs_acregmin; TYPE_1__ cfs_options; } ;
typedef  TYPE_3__ cachefs_args_t ;
typedef  int /*<<< orphan*/  ca ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int CFS_ACCESS_BACKFS ; 
 int CFS_WRITE_AROUND ; 
 int /*<<< orphan*/  DEF_FILEGRP_SIZE ; 
 int /*<<< orphan*/  DEF_POP_SIZE ; 
 int /*<<< orphan*/  MNTTAB_TYPE_CACHEFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_CACHEFS ; 
 int autofs_compute_mount_flags (TYPE_2__*) ; 
 int compute_mount_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* strpbrk (char*,char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int
mount_cachefs(char *mntdir, char *backdir, char *cachedir,
	      char *opts, int on_autofs)
{
  cachefs_args_t ca;
  mntent_t mnt;
  int flags;
  char *cp;
  MTYPE_TYPE type = MOUNT_TYPE_CACHEFS;	/* F/S mount type */

  memset((voidp) &ca, 0, sizeof(ca)); /* Paranoid */

  /*
   * Fill in the mount structure
   */
  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = backdir;
  mnt.mnt_type = MNTTAB_TYPE_CACHEFS;
  mnt.mnt_opts = opts;

  flags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    flags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */

  /* Fill in cachefs mount arguments */

  /*
   * XXX: Caveats
   * (1) cache directory is NOT checked for sanity beforehand, nor is it
   * purged.  Maybe it should be purged first?
   * (2) cache directory is NOT locked.  Should we?
   */

  /* mount flags */
  ca.cfs_options.opt_flags = CFS_WRITE_AROUND | CFS_ACCESS_BACKFS;
  /* cache population size */
  ca.cfs_options.opt_popsize = DEF_POP_SIZE; /* default: 64K */
  /* filegrp size */
  ca.cfs_options.opt_fgsize = DEF_FILEGRP_SIZE; /* default: 256 */

  /* CFS ID for file system (must be unique) */
  ca.cfs_fsid = cachedir;

  /* CFS fscdir name */
  memset(ca.cfs_cacheid, 0, sizeof(ca.cfs_cacheid));
  /*
   * Append cacheid and mountpoint.
   * sizeof(cfs_cacheid) should be C_MAX_MOUNT_FSCDIRNAME as per
   * <sys/fs/cachefs_fs.h> (checked on Solaris 8).
   */
  xsnprintf(ca.cfs_cacheid, sizeof(ca.cfs_cacheid),
	    "%s:%s", ca.cfs_fsid, mntdir);
  /* convert '/' to '_' (Solaris does that...) */
  cp = ca.cfs_cacheid;
  while ((cp = strpbrk(cp, "/")) != NULL)
    *cp = '_';

  /* path for this cache dir */
  ca.cfs_cachedir = cachedir;

  /* back filesystem dir */
  ca.cfs_backfs = backdir;

  /* same as nfs values (XXX: need to handle these options) */
  ca.cfs_acregmin = 0;
  ca.cfs_acregmax = 0;
  ca.cfs_acdirmin = 0;
  ca.cfs_acdirmax = 0;

  /*
   * Call generic mount routine
   */
  return mount_fs(&mnt, flags, (caddr_t) &ca, 0, type, 0, NULL, mnttab_file_name, on_autofs);
}