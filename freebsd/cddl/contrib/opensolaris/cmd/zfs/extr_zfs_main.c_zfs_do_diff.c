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

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int ZFS_DIFF_CLASSIFY ; 
 int ZFS_DIFF_PARSEABLE ; 
 int ZFS_DIFF_TIMESTAMP ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  sigignore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_show_diffs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int
zfs_do_diff(int argc, char **argv)
{
	zfs_handle_t *zhp;
	int flags = 0;
	char *tosnap = NULL;
	char *fromsnap = NULL;
	char *atp, *copy;
	int err = 0;
	int c;

	while ((c = getopt(argc, argv, "FHt")) != -1) {
		switch (c) {
		case 'F':
			flags |= ZFS_DIFF_CLASSIFY;
			break;
		case 'H':
			flags |= ZFS_DIFF_PARSEABLE;
			break;
		case 't':
			flags |= ZFS_DIFF_TIMESTAMP;
			break;
		default:
			(void) fprintf(stderr,
			    gettext("invalid option '%c'\n"), optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	if (argc < 1) {
		(void) fprintf(stderr,
		    gettext("must provide at least one snapshot name\n"));
		usage(B_FALSE);
	}

	if (argc > 2) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	fromsnap = argv[0];
	tosnap = (argc == 2) ? argv[1] : NULL;

	copy = NULL;
	if (*fromsnap != '@')
		copy = strdup(fromsnap);
	else if (tosnap)
		copy = strdup(tosnap);
	if (copy == NULL)
		usage(B_FALSE);

	if ((atp = strchr(copy, '@')) != NULL)
		*atp = '\0';

	if ((zhp = zfs_open(g_zfs, copy, ZFS_TYPE_FILESYSTEM)) == NULL)
		return (1);

	free(copy);

	/*
	 * Ignore SIGPIPE so that the library can give us
	 * information on any failure
	 */
	(void) sigignore(SIGPIPE);

	err = zfs_show_diffs(zhp, STDOUT_FILENO, fromsnap, tosnap, flags);

	zfs_close(zhp);

	return (err != 0);
}