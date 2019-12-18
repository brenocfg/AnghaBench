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
typedef  int /*<<< orphan*/  voidp ;
struct TYPE_6__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; int /*<<< orphan*/  mnt_type; } ;
typedef  TYPE_1__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
struct TYPE_7__ {char* fspec; int /*<<< orphan*/  version; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ efs_args_t ;
typedef  int /*<<< orphan*/  efs_args ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  EFS_MNT_VERSION ; 
 int /*<<< orphan*/  MNTTAB_TYPE_EFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_EFS ; 
 int autofs_compute_mount_flags (TYPE_1__*) ; 
 int compute_mount_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mount_efs(char *mntdir, char *fs_name, char *opts, int on_autofs)
{
  efs_args_t efs_args;
  mntent_t mnt;
  int flags;

  /*
   * Figure out the name of the file system type.
   */
  MTYPE_TYPE type = MOUNT_TYPE_EFS;

  memset((voidp) &efs_args, 0, sizeof(efs_args)); /* Paranoid */

  /*
   * Fill in the mount structure
   */
  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = fs_name;
  mnt.mnt_type = MNTTAB_TYPE_EFS;
  mnt.mnt_opts = opts;

  flags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    flags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */

#ifdef HAVE_EFS_ARGS_T_FLAGS
  efs_args.flags = 0;		/* XXX: fix this to correct flags */
#endif /* HAVE_EFS_ARGS_T_FLAGS */
#ifdef HAVE_EFS_ARGS_T_FSPEC
  efs_args.fspec = fs_name;
#endif /* HAVE_EFS_ARGS_T_FSPEC */
#if defined(HAVE_EFS_ARGS_T_VERSION) && defined(EFS_MNT_VERSION)
  efs_args.version = EFS_MNT_VERSION;
#endif /* HAVE_EFS_ARGS_T_VERSION && EFS_MNT_VERSION */

  /*
   * Call generic mount routine
   */
  return mount_fs(&mnt, flags, (caddr_t) &efs_args, 0, type, 0, NULL, mnttab_file_name, on_autofs);
}