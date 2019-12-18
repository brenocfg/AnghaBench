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
typedef  int /*<<< orphan*/  zpool_boot_label_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  ZPOOL_COPY_BOOT_LABEL ; 
 int /*<<< orphan*/  ZPOOL_NO_BOOT_LABEL ; 
 int /*<<< orphan*/  ZPOOL_PROP_BOOTSIZE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/ * make_root_vdev (int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**) ; 
 scalar_t__ num_logs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  print_vdev_tree (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zpool_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_is_bootable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 

int
zpool_do_add(int argc, char **argv)
{
	boolean_t force = B_FALSE;
	boolean_t dryrun = B_FALSE;
	int c;
	nvlist_t *nvroot;
	char *poolname;
	zpool_boot_label_t boot_type;
	uint64_t boot_size;
	int ret;
	zpool_handle_t *zhp;
	nvlist_t *config;

	/* check options */
	while ((c = getopt(argc, argv, "fn")) != -1) {
		switch (c) {
		case 'f':
			force = B_TRUE;
			break;
		case 'n':
			dryrun = B_TRUE;
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
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing vdev specification\n"));
		usage(B_FALSE);
	}

	poolname = argv[0];

	argc--;
	argv++;

	if ((zhp = zpool_open(g_zfs, poolname)) == NULL)
		return (1);

	if ((config = zpool_get_config(zhp, NULL)) == NULL) {
		(void) fprintf(stderr, gettext("pool '%s' is unavailable\n"),
		    poolname);
		zpool_close(zhp);
		return (1);
	}

	if (zpool_is_bootable(zhp))
		boot_type = ZPOOL_COPY_BOOT_LABEL;
	else
		boot_type = ZPOOL_NO_BOOT_LABEL;

	/* pass off to get_vdev_spec for processing */
	boot_size = zpool_get_prop_int(zhp, ZPOOL_PROP_BOOTSIZE, NULL);
	nvroot = make_root_vdev(zhp, force, !force, B_FALSE, dryrun,
	    boot_type, boot_size, argc, argv);
	if (nvroot == NULL) {
		zpool_close(zhp);
		return (1);
	}

	if (dryrun) {
		nvlist_t *poolnvroot;

		verify(nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
		    &poolnvroot) == 0);

		(void) printf(gettext("would update '%s' to the following "
		    "configuration:\n"), zpool_get_name(zhp));

		/* print original main pool and new tree */
		print_vdev_tree(zhp, poolname, poolnvroot, 0, B_FALSE);
		print_vdev_tree(zhp, NULL, nvroot, 0, B_FALSE);

		/* Do the same for the logs */
		if (num_logs(poolnvroot) > 0) {
			print_vdev_tree(zhp, "logs", poolnvroot, 0, B_TRUE);
			print_vdev_tree(zhp, NULL, nvroot, 0, B_TRUE);
		} else if (num_logs(nvroot) > 0) {
			print_vdev_tree(zhp, "logs", nvroot, 0, B_TRUE);
		}

		ret = 0;
	} else {
		ret = (zpool_add(zhp, nvroot) != 0);
	}

	nvlist_free(nvroot);
	zpool_close(zhp);

	return (ret);
}