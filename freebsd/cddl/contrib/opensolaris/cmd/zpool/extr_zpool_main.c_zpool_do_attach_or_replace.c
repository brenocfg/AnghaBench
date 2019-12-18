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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZPOOL_COPY_BOOT_LABEL ; 
 int /*<<< orphan*/  ZPOOL_NO_BOOT_LABEL ; 
 int /*<<< orphan*/  ZPOOL_PROP_BOOTSIZE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/ * make_root_vdev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_is_bootable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 
 int zpool_vdev_attach (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
zpool_do_attach_or_replace(int argc, char **argv, int replacing)
{
	boolean_t force = B_FALSE;
	int c;
	nvlist_t *nvroot;
	char *poolname, *old_disk, *new_disk;
	zpool_handle_t *zhp;
	zpool_boot_label_t boot_type;
	uint64_t boot_size;
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

	/* get pool name and check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing pool name argument\n"));
		usage(B_FALSE);
	}

	poolname = argv[0];

	if (argc < 2) {
		(void) fprintf(stderr,
		    gettext("missing <device> specification\n"));
		usage(B_FALSE);
	}

	old_disk = argv[1];

	if (argc < 3) {
		if (!replacing) {
			(void) fprintf(stderr,
			    gettext("missing <new_device> specification\n"));
			usage(B_FALSE);
		}
		new_disk = old_disk;
		argc -= 1;
		argv += 1;
	} else {
		new_disk = argv[2];
		argc -= 2;
		argv += 2;
	}

	if (argc > 1) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	if ((zhp = zpool_open(g_zfs, poolname)) == NULL)
		return (1);

	if (zpool_get_config(zhp, NULL) == NULL) {
		(void) fprintf(stderr, gettext("pool '%s' is unavailable\n"),
		    poolname);
		zpool_close(zhp);
		return (1);
	}

	if (zpool_is_bootable(zhp))
		boot_type = ZPOOL_COPY_BOOT_LABEL;
	else
		boot_type = ZPOOL_NO_BOOT_LABEL;

	boot_size = zpool_get_prop_int(zhp, ZPOOL_PROP_BOOTSIZE, NULL);
	nvroot = make_root_vdev(zhp, force, B_FALSE, replacing, B_FALSE,
	    boot_type, boot_size, argc, argv);
	if (nvroot == NULL) {
		zpool_close(zhp);
		return (1);
	}

	ret = zpool_vdev_attach(zhp, old_disk, new_disk, nvroot, replacing);

	nvlist_free(nvroot);
	zpool_close(zhp);

	return (ret);
}