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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  history_str ; 
 void* log_history ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  usage (void*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_disable_datasets (int /*<<< orphan*/ *,void*) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open_canfail (int /*<<< orphan*/ ,char*) ; 

int
zpool_do_destroy(int argc, char **argv)
{
	boolean_t force = B_FALSE;
	int c;
	char *pool;
	zpool_handle_t *zhp;
	int ret;

	/* check options */
	while ((c = getopt(argc, argv, "f")) != -1) {
		switch (c) {
		case 'f':
			force = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* check arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool argument\n"));
		usage(B_FALSE);
	}
	if (argc > 1) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	pool = argv[0];

	if ((zhp = zpool_open_canfail(g_zfs, pool)) == NULL) {
		/*
		 * As a special case, check for use of '/' in the name, and
		 * direct the user to use 'zfs destroy' instead.
		 */
		if (strchr(pool, '/') != NULL)
			(void) fprintf(stderr, gettext("use 'zfs destroy' to "
			    "destroy a dataset\n"));
		return (1);
	}

	if (zpool_disable_datasets(zhp, force) != 0) {
		(void) fprintf(stderr, gettext("could not destroy '%s': "
		    "could not unmount datasets\n"), zpool_get_name(zhp));
		return (1);
	}

	/* The history must be logged as part of the export */
	log_history = B_FALSE;

	ret = (zpool_destroy(zhp, history_str) != 0);

	zpool_close(zhp);

	return (ret);
}