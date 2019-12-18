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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  parseprop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ should_auto_mount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int zfs_clone (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_create_ancestors (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zfs_dataset_exists (int /*<<< orphan*/ ,char*,int) ; 
 int zfs_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_name_valid (char*,int) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_share (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_do_clone(int argc, char **argv)
{
	zfs_handle_t *zhp = NULL;
	boolean_t parents = B_FALSE;
	nvlist_t *props;
	int ret = 0;
	int c;

	if (nvlist_alloc(&props, NV_UNIQUE_NAME, 0) != 0)
		nomem();

	/* check options */
	while ((c = getopt(argc, argv, "o:p")) != -1) {
		switch (c) {
		case 'o':
			if (parseprop(props, optarg) != 0)
				return (1);
			break;
		case 'p':
			parents = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			goto usage;
		}
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing source dataset "
		    "argument\n"));
		goto usage;
	}
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing target dataset "
		    "argument\n"));
		goto usage;
	}
	if (argc > 2) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		goto usage;
	}

	/* open the source dataset */
	if ((zhp = zfs_open(g_zfs, argv[0], ZFS_TYPE_SNAPSHOT)) == NULL)
		return (1);

	if (parents && zfs_name_valid(argv[1], ZFS_TYPE_FILESYSTEM |
	    ZFS_TYPE_VOLUME)) {
		/*
		 * Now create the ancestors of the target dataset.  If the
		 * target already exists and '-p' option was used we should not
		 * complain.
		 */
		if (zfs_dataset_exists(g_zfs, argv[1], ZFS_TYPE_FILESYSTEM |
		    ZFS_TYPE_VOLUME))
			return (0);
		if (zfs_create_ancestors(g_zfs, argv[1]) != 0)
			return (1);
	}

	/* pass to libzfs */
	ret = zfs_clone(zhp, argv[1], props);

	/* create the mountpoint if necessary */
	if (ret == 0) {
		zfs_handle_t *clone;

		clone = zfs_open(g_zfs, argv[1], ZFS_TYPE_DATASET);
		if (clone != NULL) {
			/*
			 * If the user doesn't want the dataset
			 * automatically mounted, then skip the mount/share
			 * step.
			 */
			if (should_auto_mount(clone)) {
				if ((ret = zfs_mount(clone, NULL, 0)) != 0) {
					(void) fprintf(stderr, gettext("clone "
					    "successfully created, "
					    "but not mounted\n"));
				} else if ((ret = zfs_share(clone)) != 0) {
					(void) fprintf(stderr, gettext("clone "
					    "successfully created, "
					    "but not shared\n"));
				}
			}
			zfs_close(clone);
		}
	}

	zfs_close(zhp);
	nvlist_free(props);

	return (!!ret);

usage:
	if (zhp)
		zfs_close(zhp);
	nvlist_free(props);
	usage(B_FALSE);
	return (-1);
}