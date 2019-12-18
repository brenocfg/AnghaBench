#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* fspec; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ xfs_args_t ;
typedef  int /*<<< orphan*/  xfs_args ;
typedef  int /*<<< orphan*/  voidp ;
struct TYPE_7__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; int /*<<< orphan*/  mnt_type; } ;
typedef  TYPE_2__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  MNTTAB_TYPE_XFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_XFS ; 
 int autofs_compute_mount_flags (TYPE_2__*) ; 
 int compute_mount_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mount_xfs(char *mntdir, char *fs_name, char *opts, int on_autofs)
{
  xfs_args_t xfs_args;
  mntent_t mnt;
  int flags;

  /*
   * Figure out the name of the file system type.
   */
  MTYPE_TYPE type = MOUNT_TYPE_XFS;

  memset((voidp) &xfs_args, 0, sizeof(xfs_args)); /* Paranoid */

  /*
   * Fill in the mount structure
   */
  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = fs_name;
  mnt.mnt_type = MNTTAB_TYPE_XFS;
  mnt.mnt_opts = opts;

  flags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    flags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */

#ifdef HAVE_XFS_ARGS_T_FLAGS
  xfs_args.flags = 0;		/* XXX: fix this to correct flags */
#endif /* HAVE_XFS_ARGS_T_FLAGS */
#ifdef HAVE_XFS_ARGS_T_FSPEC
  xfs_args.fspec = fs_name;
#endif /* HAVE_XFS_ARGS_T_FSPEC */

  /*
   * Call generic mount routine
   */
  return mount_fs(&mnt, flags, (caddr_t) &xfs_args, 0, type, 0, NULL, mnttab_file_name, on_autofs);
}