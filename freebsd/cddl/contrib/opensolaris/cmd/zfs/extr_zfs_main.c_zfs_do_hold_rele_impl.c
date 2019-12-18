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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char const*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_hold (int /*<<< orphan*/ *,char const*,char const*,scalar_t__,int) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zfs_release (int /*<<< orphan*/ *,char const*,char const*,scalar_t__) ; 

__attribute__((used)) static int
zfs_do_hold_rele_impl(int argc, char **argv, boolean_t holding)
{
	int errors = 0;
	int i;
	const char *tag;
	boolean_t recursive = B_FALSE;
	const char *opts = holding ? "rt" : "r";
	int c;

	/* check options */
	while ((c = getopt(argc, argv, opts)) != -1) {
		switch (c) {
		case 'r':
			recursive = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc < 2)
		usage(B_FALSE);

	tag = argv[0];
	--argc;
	++argv;

	if (holding && tag[0] == '.') {
		/* tags starting with '.' are reserved for libzfs */
		(void) fprintf(stderr, gettext("tag may not start with '.'\n"));
		usage(B_FALSE);
	}

	for (i = 0; i < argc; ++i) {
		zfs_handle_t *zhp;
		char parent[ZFS_MAX_DATASET_NAME_LEN];
		const char *delim;
		char *path = argv[i];

		delim = strchr(path, '@');
		if (delim == NULL) {
			(void) fprintf(stderr,
			    gettext("'%s' is not a snapshot\n"), path);
			++errors;
			continue;
		}
		(void) strncpy(parent, path, delim - path);
		parent[delim - path] = '\0';

		zhp = zfs_open(g_zfs, parent,
		    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
		if (zhp == NULL) {
			++errors;
			continue;
		}
		if (holding) {
			if (zfs_hold(zhp, delim+1, tag, recursive, -1) != 0)
				++errors;
		} else {
			if (zfs_release(zhp, delim+1, tag, recursive) != 0)
				++errors;
		}
		zfs_close(zhp);
	}

	return (errors != 0);
}