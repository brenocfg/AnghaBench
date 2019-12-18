#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
struct TYPE_5__ {char* mnt_dir; char* mnt_fsname; char const* mnt_type; char* mnt_opts; } ;
typedef  TYPE_1__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  ext_args_t ;
typedef  int /*<<< orphan*/  ext_args ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  char* MTYPE_TYPE ;

/* Variables and functions */
 int autofs_compute_mount_flags (TYPE_1__*) ; 
 int compute_mount_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mount_ext(char *mntdir, char *fs_name, char *opts, int on_autofs, char *
    mount_type, const char *mnttab_type)
{
  ext_args_t ext_args;
  mntent_t mnt;
  int flags;

  /*
   * Figure out the name of the file system type.
   */
  MTYPE_TYPE type = mount_type;

  memset((voidp) &ext_args, 0, sizeof(ext_args)); /* Paranoid */

  /*
   * Fill in the mount structure
   */
  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = fs_name;
  mnt.mnt_type = mnttab_type;
  mnt.mnt_opts = opts;

  flags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    flags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */

  /*
   * Call generic mount routine
   */
  return mount_fs(&mnt, flags, (caddr_t) &ext_args, 0, type, 0, NULL, mnttab_file_name, on_autofs);
}