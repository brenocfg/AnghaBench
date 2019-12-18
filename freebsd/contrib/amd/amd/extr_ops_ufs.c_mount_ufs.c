#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
struct TYPE_7__ {int flags; int ufs_flags; char* fspec; int /*<<< orphan*/  ufs_pgthresh; } ;
typedef  TYPE_1__ ufs_args_t ;
typedef  int /*<<< orphan*/  ufs_args ;
struct TYPE_8__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; int /*<<< orphan*/  mnt_type; } ;
typedef  TYPE_2__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  MNTTAB_OPT_PGTHRESH ; 
 int /*<<< orphan*/  MNTTAB_TYPE_UFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_UFS ; 
 int autofs_compute_mount_flags (TYPE_2__*) ; 
 int compute_mount_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  hasmntval (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mount_ufs(char *mntdir, char *fs_name, char *opts, int on_autofs)
{
  ufs_args_t ufs_args;
  mntent_t mnt;
  int genflags;

  /*
   * Figure out the name of the file system type.
   */
  MTYPE_TYPE type = MOUNT_TYPE_UFS;

  memset((voidp) &ufs_args, 0, sizeof(ufs_args)); /* Paranoid */

  /*
   * Fill in the mount structure
   */
  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = fs_name;
  mnt.mnt_type = MNTTAB_TYPE_UFS;
  mnt.mnt_opts = opts;

  genflags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    genflags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */

#ifdef HAVE_UFS_ARGS_T_FLAGS
  ufs_args.flags = genflags;	/* XXX: is this correct? */
#endif /* HAVE_UFS_ARGS_T_FLAGS */

#ifdef HAVE_UFS_ARGS_T_UFS_FLAGS
  ufs_args.ufs_flags = genflags;
#endif /* HAVE_UFS_ARGS_T_UFS_FLAGS */

#ifdef HAVE_UFS_ARGS_T_FSPEC
  ufs_args.fspec = fs_name;
#endif /* HAVE_UFS_ARGS_T_FSPEC */

#ifdef HAVE_UFS_ARGS_T_UFS_PGTHRESH
  ufs_args.ufs_pgthresh = hasmntval(&mnt, MNTTAB_OPT_PGTHRESH);
#endif /* HAVE_UFS_ARGS_T_UFS_PGTHRESH */

  /*
   * Call generic mount routine
   */
  return mount_fs(&mnt, genflags, (caddr_t) &ufs_args, 0, type, 0, NULL, mnttab_file_name, on_autofs);
}