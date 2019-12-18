#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct statfs {int dummy; } ;
struct stat64 {scalar_t__ st_dev; } ;
struct extmnttab {char* mnt_special; int /*<<< orphan*/  mnt_fstype; int /*<<< orphan*/  mnt_minor; int /*<<< orphan*/  mnt_major; } ;
struct TYPE_4__ {int /*<<< orphan*/  libzfs_mnttab; } ;
typedef  TYPE_1__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int getextmntent (int /*<<< orphan*/ ,struct extmnttab*,int /*<<< orphan*/ ) ; 
 char* gettext (char*) ; 
 scalar_t__ makedevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 scalar_t__ stat64 (char*,struct stat64*) ; 
 int statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  statfs2mnttab (struct statfs*,struct extmnttab*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

zfs_handle_t *
zfs_path_to_zhandle(libzfs_handle_t *hdl, char *path, zfs_type_t argtype)
{
	struct stat64 statbuf;
	struct extmnttab entry;
	int ret;

	if (path[0] != '/' && strncmp(path, "./", strlen("./")) != 0) {
		/*
		 * It's not a valid path, assume it's a name of type 'argtype'.
		 */
		return (zfs_open(hdl, path, argtype));
	}

	if (stat64(path, &statbuf) != 0) {
		(void) fprintf(stderr, "%s: %s\n", path, strerror(errno));
		return (NULL);
	}

#ifdef illumos
	rewind(hdl->libzfs_mnttab);
	while ((ret = getextmntent(hdl->libzfs_mnttab, &entry, 0)) == 0) {
		if (makedevice(entry.mnt_major, entry.mnt_minor) ==
		    statbuf.st_dev) {
			break;
		}
	}
#else
	{
		struct statfs sfs;

		ret = statfs(path, &sfs);
		if (ret == 0)
			statfs2mnttab(&sfs, &entry);
		else {
			(void) fprintf(stderr, "%s: %s\n", path,
			    strerror(errno));
		}
	}
#endif	/* illumos */
	if (ret != 0) {
		return (NULL);
	}

	if (strcmp(entry.mnt_fstype, MNTTYPE_ZFS) != 0) {
		(void) fprintf(stderr, gettext("'%s': not a ZFS filesystem\n"),
		    path);
		return (NULL);
	}

	return (zfs_open(hdl, entry.mnt_special, ZFS_TYPE_FILESYSTEM));
}