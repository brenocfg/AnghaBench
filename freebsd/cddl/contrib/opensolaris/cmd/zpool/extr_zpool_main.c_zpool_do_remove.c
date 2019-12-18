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
typedef  int /*<<< orphan*/  valstr ;
typedef  char* uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 char getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int /*<<< orphan*/  zfs_nicenum (char*,char*,int) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zpool_vdev_indirect_size (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ zpool_vdev_remove (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ zpool_vdev_remove_cancel (int /*<<< orphan*/ *) ; 

int
zpool_do_remove(int argc, char **argv)
{
	char *poolname;
	int i, ret = 0;
	zpool_handle_t *zhp;
	boolean_t stop = B_FALSE;
	boolean_t noop = B_FALSE;
	boolean_t parsable = B_FALSE;
	char c;

	/* check options */
	while ((c = getopt(argc, argv, "nps")) != -1) {
		switch (c) {
		case 'n':
			noop = B_TRUE;
			break;
		case 'p':
			parsable = B_TRUE;
			break;
		case 's':
			stop = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* get pool name and check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool name argument\n"));
		usage(B_FALSE);
	}

	poolname = argv[0];

	if ((zhp = zpool_open(g_zfs, poolname)) == NULL)
		return (1);

	if (stop && noop) {
		(void) fprintf(stderr, gettext("stop request ignored\n"));
		return (0);
	}

	if (stop) {
		if (argc > 1) {
			(void) fprintf(stderr, gettext("too many arguments\n"));
			usage(B_FALSE);
		}
		if (zpool_vdev_remove_cancel(zhp) != 0)
			ret = 1;
	} else {
		if (argc < 2) {
			(void) fprintf(stderr, gettext("missing device\n"));
			usage(B_FALSE);
		}

		for (i = 1; i < argc; i++) {
			if (noop) {
				uint64_t size;

				if (zpool_vdev_indirect_size(zhp, argv[i],
				    &size) != 0) {
					ret = 1;
					break;
				}
				if (parsable) {
					(void) printf("%s %llu\n",
					    argv[i], size);
				} else {
					char valstr[32];
					zfs_nicenum(size, valstr,
					    sizeof (valstr));
					(void) printf("Memory that will be "
					    "used after removing %s: %s\n",
					    argv[i], valstr);
				}
			} else {
				if (zpool_vdev_remove(zhp, argv[i]) != 0)
					ret = 1;
			}
		}
	}

	return (ret);
}