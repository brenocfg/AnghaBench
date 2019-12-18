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
typedef  scalar_t__ uint64_t ;
struct mnttab {char* mnt_mntopts; } ;
typedef  int /*<<< orphan*/  smbshareopts ;
typedef  int /*<<< orphan*/  shareopts ;
typedef  int /*<<< orphan*/  mountpoint ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ GLOBAL_ZONEID ; 
 int /*<<< orphan*/  MNTOPT_REMOUNT ; 
#define  OP_MOUNT 129 
#define  OP_SHARE 128 
 scalar_t__ ZFS_CANMOUNT_NOAUTO ; 
 scalar_t__ ZFS_CANMOUNT_OFF ; 
 int ZFS_MAXPROPLEN ; 
 int /*<<< orphan*/  ZFS_PROP_CANMOUNT ; 
 int /*<<< orphan*/  ZFS_PROP_INCONSISTENT ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_RECEIVE_RESUME_TOKEN ; 
 int /*<<< orphan*/  ZFS_PROP_SHARENFS ; 
 int /*<<< orphan*/  ZFS_PROP_SHARESMB ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 scalar_t__ getzoneid () ; 
 int /*<<< orphan*/  hasmntopt (struct mnttab*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  verify (int) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int zfs_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_is_mounted (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_is_shared_nfs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_is_shared_smb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_mount (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_share_nfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_share_smb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_shareall (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
share_mount_one(zfs_handle_t *zhp, int op, int flags, char *protocol,
    boolean_t explicit, const char *options)
{
	char mountpoint[ZFS_MAXPROPLEN];
	char shareopts[ZFS_MAXPROPLEN];
	char smbshareopts[ZFS_MAXPROPLEN];
	const char *cmdname = op == OP_SHARE ? "share" : "mount";
	struct mnttab mnt;
	uint64_t zoned, canmount;
	boolean_t shared_nfs, shared_smb;

	assert(zfs_get_type(zhp) & ZFS_TYPE_FILESYSTEM);

	/*
	 * Check to make sure we can mount/share this dataset.  If we
	 * are in the global zone and the filesystem is exported to a
	 * local zone, or if we are in a local zone and the
	 * filesystem is not exported, then it is an error.
	 */
	zoned = zfs_prop_get_int(zhp, ZFS_PROP_ZONED);

	if (zoned && getzoneid() == GLOBAL_ZONEID) {
		if (!explicit)
			return (0);

		(void) fprintf(stderr, gettext("cannot %s '%s': "
		    "dataset is exported to a local zone\n"), cmdname,
		    zfs_get_name(zhp));
		return (1);

	} else if (!zoned && getzoneid() != GLOBAL_ZONEID) {
		if (!explicit)
			return (0);

		(void) fprintf(stderr, gettext("cannot %s '%s': "
		    "permission denied\n"), cmdname,
		    zfs_get_name(zhp));
		return (1);
	}

	/*
	 * Ignore any filesystems which don't apply to us. This
	 * includes those with a legacy mountpoint, or those with
	 * legacy share options.
	 */
	verify(zfs_prop_get(zhp, ZFS_PROP_MOUNTPOINT, mountpoint,
	    sizeof (mountpoint), NULL, NULL, 0, B_FALSE) == 0);
	verify(zfs_prop_get(zhp, ZFS_PROP_SHARENFS, shareopts,
	    sizeof (shareopts), NULL, NULL, 0, B_FALSE) == 0);
	verify(zfs_prop_get(zhp, ZFS_PROP_SHARESMB, smbshareopts,
	    sizeof (smbshareopts), NULL, NULL, 0, B_FALSE) == 0);

	if (op == OP_SHARE && strcmp(shareopts, "off") == 0 &&
	    strcmp(smbshareopts, "off") == 0) {
		if (!explicit)
			return (0);

		(void) fprintf(stderr, gettext("cannot share '%s': "
		    "legacy share\n"), zfs_get_name(zhp));
		(void) fprintf(stderr, gettext("to "
		    "share this filesystem set "
		    "sharenfs property on\n"));
		return (1);
	}

	/*
	 * We cannot share or mount legacy filesystems. If the
	 * shareopts is non-legacy but the mountpoint is legacy, we
	 * treat it as a legacy share.
	 */
	if (strcmp(mountpoint, "legacy") == 0) {
		if (!explicit)
			return (0);

		(void) fprintf(stderr, gettext("cannot %s '%s': "
		    "legacy mountpoint\n"), cmdname, zfs_get_name(zhp));
		(void) fprintf(stderr, gettext("use %s(8) to "
		    "%s this filesystem\n"), cmdname, cmdname);
		return (1);
	}

	if (strcmp(mountpoint, "none") == 0) {
		if (!explicit)
			return (0);

		(void) fprintf(stderr, gettext("cannot %s '%s': no "
		    "mountpoint set\n"), cmdname, zfs_get_name(zhp));
		return (1);
	}

	/*
	 * canmount	explicit	outcome
	 * on		no		pass through
	 * on		yes		pass through
	 * off		no		return 0
	 * off		yes		display error, return 1
	 * noauto	no		return 0
	 * noauto	yes		pass through
	 */
	canmount = zfs_prop_get_int(zhp, ZFS_PROP_CANMOUNT);
	if (canmount == ZFS_CANMOUNT_OFF) {
		if (!explicit)
			return (0);

		(void) fprintf(stderr, gettext("cannot %s '%s': "
		    "'canmount' property is set to 'off'\n"), cmdname,
		    zfs_get_name(zhp));
		return (1);
	} else if (canmount == ZFS_CANMOUNT_NOAUTO && !explicit) {
		return (0);
	}

	/*
	 * If this filesystem is inconsistent and has a receive resume
	 * token, we can not mount it.
	 */
	if (zfs_prop_get_int(zhp, ZFS_PROP_INCONSISTENT) &&
	    zfs_prop_get(zhp, ZFS_PROP_RECEIVE_RESUME_TOKEN,
	    NULL, 0, NULL, NULL, 0, B_TRUE) == 0) {
		if (!explicit)
			return (0);

		(void) fprintf(stderr, gettext("cannot %s '%s': "
		    "Contains partially-completed state from "
		    "\"zfs receive -r\", which can be resumed with "
		    "\"zfs send -t\"\n"),
		    cmdname, zfs_get_name(zhp));
		return (1);
	}

	/*
	 * At this point, we have verified that the mountpoint and/or
	 * shareopts are appropriate for auto management. If the
	 * filesystem is already mounted or shared, return (failing
	 * for explicit requests); otherwise mount or share the
	 * filesystem.
	 */
	switch (op) {
	case OP_SHARE:

		shared_nfs = zfs_is_shared_nfs(zhp, NULL);
		shared_smb = zfs_is_shared_smb(zhp, NULL);

		if ((shared_nfs && shared_smb) ||
		    (shared_nfs && strcmp(shareopts, "on") == 0 &&
		    strcmp(smbshareopts, "off") == 0) ||
		    (shared_smb && strcmp(smbshareopts, "on") == 0 &&
		    strcmp(shareopts, "off") == 0)) {
			if (!explicit)
				return (0);

			(void) fprintf(stderr, gettext("cannot share "
			    "'%s': filesystem already shared\n"),
			    zfs_get_name(zhp));
			return (1);
		}

		if (!zfs_is_mounted(zhp, NULL) &&
		    zfs_mount(zhp, NULL, 0) != 0)
			return (1);

		if (protocol == NULL) {
			if (zfs_shareall(zhp) != 0)
				return (1);
		} else if (strcmp(protocol, "nfs") == 0) {
			if (zfs_share_nfs(zhp))
				return (1);
		} else if (strcmp(protocol, "smb") == 0) {
			if (zfs_share_smb(zhp))
				return (1);
		} else {
			(void) fprintf(stderr, gettext("cannot share "
			    "'%s': invalid share type '%s' "
			    "specified\n"),
			    zfs_get_name(zhp), protocol);
			return (1);
		}

		break;

	case OP_MOUNT:
		if (options == NULL)
			mnt.mnt_mntopts = "";
		else
			mnt.mnt_mntopts = (char *)options;

		if (!hasmntopt(&mnt, MNTOPT_REMOUNT) &&
		    zfs_is_mounted(zhp, NULL)) {
			if (!explicit)
				return (0);

			(void) fprintf(stderr, gettext("cannot mount "
			    "'%s': filesystem already mounted\n"),
			    zfs_get_name(zhp));
			return (1);
		}

		if (zfs_mount(zhp, options, flags) != 0)
			return (1);
		break;
	}

	return (0);
}