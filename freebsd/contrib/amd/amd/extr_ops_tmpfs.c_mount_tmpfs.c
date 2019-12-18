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
struct TYPE_7__ {int /*<<< orphan*/  ta_root_mode; void* ta_root_gid; void* ta_root_uid; void* ta_size_max; void* ta_nodes_max; int /*<<< orphan*/  ta_version; } ;
typedef  TYPE_1__ tmpfs_args_t ;
typedef  int /*<<< orphan*/  tmpfs_args ;
struct TYPE_8__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; int /*<<< orphan*/  mnt_type; } ;
typedef  TYPE_2__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  MNTTAB_TYPE_TMPFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_TMPFS ; 
 int /*<<< orphan*/  TMPFS_ARGS_VERSION ; 
 char* amu_hasmntopt (TYPE_2__*,char*) ; 
 void* atoi (char const*) ; 
 int autofs_compute_mount_flags (TYPE_2__*) ; 
 int compute_mount_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mount_tmpfs(char *mntdir, char *fs_name, char *opts, int on_autofs)
{
  tmpfs_args_t tmpfs_args;
  mntent_t mnt;
  int flags;
  const char *p;

  /*
   * Figure out the name of the file system type.
   */
  MTYPE_TYPE type = MOUNT_TYPE_TMPFS;

  p = NULL;
  memset((voidp) &tmpfs_args, 0, sizeof(tmpfs_args)); /* Paranoid */

  /*
   * Fill in the mount structure
   */
  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = fs_name;
  mnt.mnt_type = MNTTAB_TYPE_TMPFS;
  mnt.mnt_opts = opts;

  flags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    flags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */

#if defined(HAVE_TMPFS_ARGS_T_TA_VERSION) && defined(TMPFS_ARGS_VERSION)
  tmpfs_args.ta_version = TMPFS_ARGS_VERSION;
#endif /* HAVE_TMPFS_ARGS_T_TA_VERSION && TMPFS_ARGS_VERSION */
#ifdef HAVE_TMPFS_ARGS_T_TA_NODES_MAX
  if ((p = amu_hasmntopt(&mnt, "nodes")) == NULL)
	p = "1000000";
  tmpfs_args.ta_nodes_max = atoi(p);
#endif /* HAVE_TMPFS_ARGS_T_TA_SIZE_MAX */
#ifdef HAVE_TMPFS_ARGS_T_TA_SIZE_MAX
  if ((p = amu_hasmntopt(&mnt, "size")) == NULL)
	p = "10000000";
  tmpfs_args.ta_size_max = atoi(p);
#endif /* HAVE_TMPFS_ARGS_T_TA_SIZE_MAX */
#ifdef HAVE_TMPFS_ARGS_T_TA_ROOT_UID
  if ((p = amu_hasmntopt(&mnt, "uid")) == NULL)
	p = "0";
  tmpfs_args.ta_root_uid = atoi(p);
#endif /* HAVE_TMPFS_ARGS_T_TA_ROOT_UID */
#ifdef HAVE_TMPFS_ARGS_T_TA_ROOT_GID
  if ((p = amu_hasmntopt(&mnt, "gid")) == NULL)
	p = "0";
  tmpfs_args.ta_root_gid = atoi(p);
#endif /* HAVE_TMPFS_ARGS_T_TA_ROOT_GID */
#ifdef HAVE_TMPFS_ARGS_T_TA_ROOT_MODE
  if ((p = amu_hasmntopt(&mnt, "mode")) == NULL)
	p = "01777";
  tmpfs_args.ta_root_mode = strtol(p, NULL, 8);
#endif /* HAVE_TMPFS_ARGS_T_TA_ROOT_MODE */

  /*
   * Call generic mount routine
   */
  return mount_fs(&mnt, flags, (caddr_t) &tmpfs_args, 0, type, 0, NULL, mnttab_file_name, on_autofs);
}