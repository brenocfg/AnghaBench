#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_3__ {char* cb_propname; scalar_t__ cb_received; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ inherit_cbdata_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int ZFS_ITER_RECURSE ; 
 scalar_t__ ZFS_PROP_QUOTA ; 
 scalar_t__ ZFS_PROP_REFQUOTA ; 
 scalar_t__ ZFS_PROP_REFRESERVATION ; 
 scalar_t__ ZFS_PROP_RESERVATION ; 
 scalar_t__ ZFS_PROP_VERSION ; 
 scalar_t__ ZFS_PROP_VOLSIZE ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  inherit_cb ; 
 int /*<<< orphan*/  inherit_recurse_cb ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int zfs_for_each (int,char**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ zfs_name_to_prop (char*) ; 
 int /*<<< orphan*/  zfs_prop_inheritable (scalar_t__) ; 
 scalar_t__ zfs_prop_readonly (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_user (char*) ; 

__attribute__((used)) static int
zfs_do_inherit(int argc, char **argv)
{
	int c;
	zfs_prop_t prop;
	inherit_cbdata_t cb = { 0 };
	char *propname;
	int ret = 0;
	int flags = 0;
	boolean_t received = B_FALSE;

	/* check options */
	while ((c = getopt(argc, argv, "rS")) != -1) {
		switch (c) {
		case 'r':
			flags |= ZFS_ITER_RECURSE;
			break;
		case 'S':
			received = B_TRUE;
			break;
		case '?':
		default:
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing property argument\n"));
		usage(B_FALSE);
	}
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing dataset argument\n"));
		usage(B_FALSE);
	}

	propname = argv[0];
	argc--;
	argv++;

	if ((prop = zfs_name_to_prop(propname)) != ZPROP_INVAL) {
		if (zfs_prop_readonly(prop)) {
			(void) fprintf(stderr, gettext(
			    "%s property is read-only\n"),
			    propname);
			return (1);
		}
		if (!zfs_prop_inheritable(prop) && !received) {
			(void) fprintf(stderr, gettext("'%s' property cannot "
			    "be inherited\n"), propname);
			if (prop == ZFS_PROP_QUOTA ||
			    prop == ZFS_PROP_RESERVATION ||
			    prop == ZFS_PROP_REFQUOTA ||
			    prop == ZFS_PROP_REFRESERVATION) {
				(void) fprintf(stderr, gettext("use 'zfs set "
				    "%s=none' to clear\n"), propname);
				(void) fprintf(stderr, gettext("use 'zfs "
				    "inherit -S %s' to revert to received "
				    "value\n"), propname);
			}
			return (1);
		}
		if (received && (prop == ZFS_PROP_VOLSIZE ||
		    prop == ZFS_PROP_VERSION)) {
			(void) fprintf(stderr, gettext("'%s' property cannot "
			    "be reverted to a received value\n"), propname);
			return (1);
		}
	} else if (!zfs_prop_user(propname)) {
		(void) fprintf(stderr, gettext("invalid property '%s'\n"),
		    propname);
		usage(B_FALSE);
	}

	cb.cb_propname = propname;
	cb.cb_received = received;

	if (flags & ZFS_ITER_RECURSE) {
		ret = zfs_for_each(argc, argv, flags, ZFS_TYPE_DATASET,
		    NULL, NULL, 0, inherit_recurse_cb, &cb);
	} else {
		ret = zfs_for_each(argc, argv, flags, ZFS_TYPE_DATASET,
		    NULL, NULL, 0, inherit_cb, &cb);
	}

	return (ret);
}