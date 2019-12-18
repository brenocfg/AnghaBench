#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int zfs_type_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_8__ {void* cb_defer_destroy; char* cb_snapspec; char* cb_snapused; void* cb_nvl; void* cb_batchedsnaps; scalar_t__ cb_error; void* cb_doclones; void* cb_first; void* cb_recurse; int /*<<< orphan*/ * cb_target; void* cb_dryrun; void* cb_parsable; void* cb_verbose; void* cb_force; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ destroy_cbdata_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int ZFS_TYPE_DATASET ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_SNAPSHOT ; 
 int ZFS_TYPE_VOLUME ; 
 int destroy_callback (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int destroy_check_dependent (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int destroy_clones (TYPE_1__*) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 void* fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (void*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 scalar_t__ gather_snapshots (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int lzc_destroy_bookmarks (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_empty (void*) ; 
 int /*<<< orphan*/  nvlist_free (void*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  usage (void*) ; 
 int /*<<< orphan*/  zfs_bookmark_exists (char*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_destroy_snaps_nvl (int /*<<< orphan*/ ,void*,void*) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int zfs_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_handle_dup (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_iter_dependents (int /*<<< orphan*/ *,void*,int (*) (int /*<<< orphan*/ *,TYPE_1__*),TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_nicenum (char*,char*,int) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
zfs_do_destroy(int argc, char **argv)
{
	destroy_cbdata_t cb = { 0 };
	int rv = 0;
	int err = 0;
	int c;
	zfs_handle_t *zhp = NULL;
	char *at, *pound;
	zfs_type_t type = ZFS_TYPE_DATASET;

	/* check options */
	while ((c = getopt(argc, argv, "vpndfrR")) != -1) {
		switch (c) {
		case 'v':
			cb.cb_verbose = B_TRUE;
			break;
		case 'p':
			cb.cb_verbose = B_TRUE;
			cb.cb_parsable = B_TRUE;
			break;
		case 'n':
			cb.cb_dryrun = B_TRUE;
			break;
		case 'd':
			cb.cb_defer_destroy = B_TRUE;
			type = ZFS_TYPE_SNAPSHOT;
			break;
		case 'f':
			cb.cb_force = B_TRUE;
			break;
		case 'r':
			cb.cb_recurse = B_TRUE;
			break;
		case 'R':
			cb.cb_recurse = B_TRUE;
			cb.cb_doclones = B_TRUE;
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
	if (argc == 0) {
		(void) fprintf(stderr, gettext("missing dataset argument\n"));
		usage(B_FALSE);
	}
	if (argc > 1) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	at = strchr(argv[0], '@');
	pound = strchr(argv[0], '#');
	if (at != NULL) {

		/* Build the list of snaps to destroy in cb_nvl. */
		cb.cb_nvl = fnvlist_alloc();

		*at = '\0';
		zhp = zfs_open(g_zfs, argv[0],
		    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
		if (zhp == NULL)
			return (1);

		cb.cb_snapspec = at + 1;
		if (gather_snapshots(zfs_handle_dup(zhp), &cb) != 0 ||
		    cb.cb_error) {
			rv = 1;
			goto out;
		}

		if (nvlist_empty(cb.cb_nvl)) {
			(void) fprintf(stderr, gettext("could not find any "
			    "snapshots to destroy; check snapshot names.\n"));
			rv = 1;
			goto out;
		}

		if (cb.cb_verbose) {
			char buf[16];
			zfs_nicenum(cb.cb_snapused, buf, sizeof (buf));
			if (cb.cb_parsable) {
				(void) printf("reclaim\t%llu\n",
				    cb.cb_snapused);
			} else if (cb.cb_dryrun) {
				(void) printf(gettext("would reclaim %s\n"),
				    buf);
			} else {
				(void) printf(gettext("will reclaim %s\n"),
				    buf);
			}
		}

		if (!cb.cb_dryrun) {
			if (cb.cb_doclones) {
				cb.cb_batchedsnaps = fnvlist_alloc();
				err = destroy_clones(&cb);
				if (err == 0) {
					err = zfs_destroy_snaps_nvl(g_zfs,
					    cb.cb_batchedsnaps, B_FALSE);
				}
				if (err != 0) {
					rv = 1;
					goto out;
				}
			}
			if (err == 0) {
				err = zfs_destroy_snaps_nvl(g_zfs, cb.cb_nvl,
				    cb.cb_defer_destroy);
			}
		}

		if (err != 0)
			rv = 1;
	} else if (pound != NULL) {
		int err;
		nvlist_t *nvl;

		if (cb.cb_dryrun) {
			(void) fprintf(stderr,
			    "dryrun is not supported with bookmark\n");
			return (-1);
		}

		if (cb.cb_defer_destroy) {
			(void) fprintf(stderr,
			    "defer destroy is not supported with bookmark\n");
			return (-1);
		}

		if (cb.cb_recurse) {
			(void) fprintf(stderr,
			    "recursive is not supported with bookmark\n");
			return (-1);
		}

		if (!zfs_bookmark_exists(argv[0])) {
			(void) fprintf(stderr, gettext("bookmark '%s' "
			    "does not exist.\n"), argv[0]);
			return (1);
		}

		nvl = fnvlist_alloc();
		fnvlist_add_boolean(nvl, argv[0]);

		err = lzc_destroy_bookmarks(nvl, NULL);
		if (err != 0) {
			(void) zfs_standard_error(g_zfs, err,
			    "cannot destroy bookmark");
		}

		nvlist_free(cb.cb_nvl);

		return (err);
	} else {
		/* Open the given dataset */
		if ((zhp = zfs_open(g_zfs, argv[0], type)) == NULL)
			return (1);

		cb.cb_target = zhp;

		/*
		 * Perform an explicit check for pools before going any further.
		 */
		if (!cb.cb_recurse && strchr(zfs_get_name(zhp), '/') == NULL &&
		    zfs_get_type(zhp) == ZFS_TYPE_FILESYSTEM) {
			(void) fprintf(stderr, gettext("cannot destroy '%s': "
			    "operation does not apply to pools\n"),
			    zfs_get_name(zhp));
			(void) fprintf(stderr, gettext("use 'zfs destroy -r "
			    "%s' to destroy all datasets in the pool\n"),
			    zfs_get_name(zhp));
			(void) fprintf(stderr, gettext("use 'zpool destroy %s' "
			    "to destroy the pool itself\n"), zfs_get_name(zhp));
			rv = 1;
			goto out;
		}

		/*
		 * Check for any dependents and/or clones.
		 */
		cb.cb_first = B_TRUE;
		if (!cb.cb_doclones &&
		    zfs_iter_dependents(zhp, B_TRUE, destroy_check_dependent,
		    &cb) != 0) {
			rv = 1;
			goto out;
		}

		if (cb.cb_error) {
			rv = 1;
			goto out;
		}

		cb.cb_batchedsnaps = fnvlist_alloc();
		if (zfs_iter_dependents(zhp, B_FALSE, destroy_callback,
		    &cb) != 0) {
			rv = 1;
			goto out;
		}

		/*
		 * Do the real thing.  The callback will close the
		 * handle regardless of whether it succeeds or not.
		 */
		err = destroy_callback(zhp, &cb);
		zhp = NULL;
		if (err == 0) {
			err = zfs_destroy_snaps_nvl(g_zfs,
			    cb.cb_batchedsnaps, cb.cb_defer_destroy);
		}
		if (err != 0)
			rv = 1;
	}

out:
	fnvlist_free(cb.cb_batchedsnaps);
	fnvlist_free(cb.cb_nvl);
	if (zhp != NULL)
		zfs_close(zhp);
	return (rv);
}