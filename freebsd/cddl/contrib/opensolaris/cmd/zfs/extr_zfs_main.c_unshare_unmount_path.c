#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct statfs {int dummy; } ;
struct stat64 {scalar_t__ st_ino; int /*<<< orphan*/  st_dev; } ;
struct extmnttab {scalar_t__ mnt_major; scalar_t__ mnt_minor; char* mnt_fstype; char* mnt_mountp; int /*<<< orphan*/  mnt_special; } ;
typedef  int /*<<< orphan*/  smbshare_prop ;
typedef  int /*<<< orphan*/  nfs_mnt_prop ;
typedef  int /*<<< orphan*/  mtpt_prop ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 char* MNTTYPE_ZFS ; 
 int OP_SHARE ; 
 int ZFS_MAXPROPLEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_SHARENFS ; 
 int /*<<< orphan*/  ZFS_PROP_SHARESMB ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getextmntent (int /*<<< orphan*/ ,struct extmnttab*,int /*<<< orphan*/ ) ; 
 char* gettext (char*) ; 
 scalar_t__ major (int /*<<< orphan*/ ) ; 
 scalar_t__ minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnttab_file ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 scalar_t__ stat64 (char*,struct stat64*) ; 
 scalar_t__ statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  statfs2mnttab (struct statfs*,struct extmnttab*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int umount2 (char*,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_is_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfs_unmount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zfs_unmountall (int /*<<< orphan*/ *,int) ; 
 int zfs_unshareall_bypath (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
unshare_unmount_path(int op, char *path, int flags, boolean_t is_manual)
{
	zfs_handle_t *zhp;
	int ret = 0;
	struct stat64 statbuf;
	struct extmnttab entry;
	const char *cmdname = (op == OP_SHARE) ? "unshare" : "unmount";
	ino_t path_inode;

	/*
	 * Search for the path in /etc/mnttab.  Rather than looking for the
	 * specific path, which can be fooled by non-standard paths (i.e. ".."
	 * or "//"), we stat() the path and search for the corresponding
	 * (major,minor) device pair.
	 */
	if (stat64(path, &statbuf) != 0) {
		(void) fprintf(stderr, gettext("cannot %s '%s': %s\n"),
		    cmdname, path, strerror(errno));
		return (1);
	}
	path_inode = statbuf.st_ino;

	/*
	 * Search for the given (major,minor) pair in the mount table.
	 */
#ifdef illumos
	rewind(mnttab_file);
	while ((ret = getextmntent(mnttab_file, &entry, 0)) == 0) {
		if (entry.mnt_major == major(statbuf.st_dev) &&
		    entry.mnt_minor == minor(statbuf.st_dev))
			break;
	}
#else
	{
		struct statfs sfs;

		if (statfs(path, &sfs) != 0) {
			(void) fprintf(stderr, "%s: %s\n", path,
			    strerror(errno));
			ret = -1;
		}
		statfs2mnttab(&sfs, &entry);
	}
#endif
	if (ret != 0) {
		if (op == OP_SHARE) {
			(void) fprintf(stderr, gettext("cannot %s '%s': not "
			    "currently mounted\n"), cmdname, path);
			return (1);
		}
		(void) fprintf(stderr, gettext("warning: %s not in mnttab\n"),
		    path);
		if ((ret = umount2(path, flags)) != 0)
			(void) fprintf(stderr, gettext("%s: %s\n"), path,
			    strerror(errno));
		return (ret != 0);
	}

	if (strcmp(entry.mnt_fstype, MNTTYPE_ZFS) != 0) {
		(void) fprintf(stderr, gettext("cannot %s '%s': not a ZFS "
		    "filesystem\n"), cmdname, path);
		return (1);
	}

	if ((zhp = zfs_open(g_zfs, entry.mnt_special,
	    ZFS_TYPE_FILESYSTEM)) == NULL)
		return (1);

	ret = 1;
	if (stat64(entry.mnt_mountp, &statbuf) != 0) {
		(void) fprintf(stderr, gettext("cannot %s '%s': %s\n"),
		    cmdname, path, strerror(errno));
		goto out;
	} else if (statbuf.st_ino != path_inode) {
		(void) fprintf(stderr, gettext("cannot "
		    "%s '%s': not a mountpoint\n"), cmdname, path);
		goto out;
	}

	if (op == OP_SHARE) {
		char nfs_mnt_prop[ZFS_MAXPROPLEN];
		char smbshare_prop[ZFS_MAXPROPLEN];

		verify(zfs_prop_get(zhp, ZFS_PROP_SHARENFS, nfs_mnt_prop,
		    sizeof (nfs_mnt_prop), NULL, NULL, 0, B_FALSE) == 0);
		verify(zfs_prop_get(zhp, ZFS_PROP_SHARESMB, smbshare_prop,
		    sizeof (smbshare_prop), NULL, NULL, 0, B_FALSE) == 0);

		if (strcmp(nfs_mnt_prop, "off") == 0 &&
		    strcmp(smbshare_prop, "off") == 0) {
			(void) fprintf(stderr, gettext("cannot unshare "
			    "'%s': legacy share\n"), path);
#ifdef illumos
			(void) fprintf(stderr, gettext("use "
			    "unshare(1M) to unshare this filesystem\n"));
#endif
		} else if (!zfs_is_shared(zhp)) {
			(void) fprintf(stderr, gettext("cannot unshare '%s': "
			    "not currently shared\n"), path);
		} else {
			ret = zfs_unshareall_bypath(zhp, path);
		}
	} else {
		char mtpt_prop[ZFS_MAXPROPLEN];

		verify(zfs_prop_get(zhp, ZFS_PROP_MOUNTPOINT, mtpt_prop,
		    sizeof (mtpt_prop), NULL, NULL, 0, B_FALSE) == 0);

		if (is_manual) {
			ret = zfs_unmount(zhp, NULL, flags);
		} else if (strcmp(mtpt_prop, "legacy") == 0) {
			(void) fprintf(stderr, gettext("cannot unmount "
			    "'%s': legacy mountpoint\n"),
			    zfs_get_name(zhp));
			(void) fprintf(stderr, gettext("use umount(8) "
			    "to unmount this filesystem\n"));
		} else {
			ret = zfs_unmountall(zhp, flags);
		}
	}

out:
	zfs_close(zhp);

	return (ret != 0);
}