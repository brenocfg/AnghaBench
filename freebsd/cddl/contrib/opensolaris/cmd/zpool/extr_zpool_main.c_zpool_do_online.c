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
typedef  scalar_t__ vdev_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ VDEV_STATE_FAULTED ; 
 scalar_t__ VDEV_STATE_HEALTHY ; 
 int ZFS_ONLINE_EXPAND ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zpool_vdev_online (int /*<<< orphan*/ *,char*,int,scalar_t__*) ; 

int
zpool_do_online(int argc, char **argv)
{
	int c, i;
	char *poolname;
	zpool_handle_t *zhp;
	int ret = 0;
	vdev_state_t newstate;
	int flags = 0;

	/* check options */
	while ((c = getopt(argc, argv, "et")) != -1) {
		switch (c) {
		case 'e':
			flags |= ZFS_ONLINE_EXPAND;
			break;
		case 't':
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
		(void) fprintf(stderr, gettext("missing pool name\n"));
		usage(B_FALSE);
	}
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing device name\n"));
		usage(B_FALSE);
	}

	poolname = argv[0];

	if ((zhp = zpool_open(g_zfs, poolname)) == NULL)
		return (1);

	for (i = 1; i < argc; i++) {
		if (zpool_vdev_online(zhp, argv[i], flags, &newstate) == 0) {
			if (newstate != VDEV_STATE_HEALTHY) {
				(void) printf(gettext("warning: device '%s' "
				    "onlined, but remains in faulted state\n"),
				    argv[i]);
				if (newstate == VDEV_STATE_FAULTED)
					(void) printf(gettext("use 'zpool "
					    "clear' to restore a faulted "
					    "device\n"));
				else
					(void) printf(gettext("use 'zpool "
					    "replace' to replace devices "
					    "that are no longer present\n"));
			}
		} else {
			ret = 1;
		}
	}

	zpool_close(zhp);

	return (ret);
}