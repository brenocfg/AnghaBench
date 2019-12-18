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
 int /*<<< orphan*/  usage (void*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_disable_datasets (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ zpool_export (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_export_force (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zpool_open_canfail (int /*<<< orphan*/ ,char*) ; 

int
zpool_do_export(int argc, char **argv)
{
	boolean_t force = B_FALSE;
	boolean_t hardforce = B_FALSE;
	int c;
	zpool_handle_t *zhp;
	int ret;
	int i;

	/* check options */
	while ((c = getopt(argc, argv, "fF")) != -1) {
		switch (c) {
		case 'f':
			force = B_TRUE;
			break;
		case 'F':
			hardforce = B_TRUE;
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

	ret = 0;
	for (i = 0; i < argc; i++) {
		if ((zhp = zpool_open_canfail(g_zfs, argv[i])) == NULL) {
			ret = 1;
			continue;
		}

		if (zpool_disable_datasets(zhp, force) != 0) {
			ret = 1;
			zpool_close(zhp);
			continue;
		}

		/* The history must be logged as part of the export */
		log_history = B_FALSE;

		if (hardforce) {
			if (zpool_export_force(zhp, history_str) != 0)
				ret = 1;
		} else if (zpool_export(zhp, force, history_str) != 0) {
			ret = 1;
		}

		zpool_close(zhp);
	}

	return (ret);
}