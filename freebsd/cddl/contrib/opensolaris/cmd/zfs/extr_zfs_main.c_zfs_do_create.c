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
typedef  scalar_t__ zfs_type_t ;
typedef  int /*<<< orphan*/  zfs_prop_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 scalar_t__ SPA_VERSION_REFRESERVATION ; 
 int /*<<< orphan*/  ZFS_PROP_REFRESERVATION ; 
 int /*<<< orphan*/  ZFS_PROP_RESERVATION ; 
 int /*<<< orphan*/  ZFS_PROP_VOLBLOCKSIZE ; 
 int /*<<< orphan*/  ZFS_PROP_VOLSIZE ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  ZPOOL_PROP_VERSION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 char* libzfs_error_description (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  parseprop (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ should_auto_mount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_create (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_create_ancestors (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zfs_dataset_exists (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ zfs_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_name_valid (char*,scalar_t__) ; 
 int /*<<< orphan*/  zfs_nicestrtonum (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_share (int /*<<< orphan*/ *) ; 
 char* zfs_type_to_name (scalar_t__) ; 
 int /*<<< orphan*/ * zfs_valid_proplist (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zvol_volsize_to_reservation (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_do_create(int argc, char **argv)
{
	zfs_type_t type = ZFS_TYPE_FILESYSTEM;
	zfs_handle_t *zhp = NULL;
	uint64_t volsize = 0;
	int c;
	boolean_t noreserve = B_FALSE;
	boolean_t bflag = B_FALSE;
	boolean_t parents = B_FALSE;
	boolean_t nomount = B_FALSE;
	int ret = 1;
	nvlist_t *props;
	uint64_t intval;

	if (nvlist_alloc(&props, NV_UNIQUE_NAME, 0) != 0)
		nomem();

	/* check options */
	while ((c = getopt(argc, argv, ":V:b:so:pu")) != -1) {
		switch (c) {
		case 'V':
			type = ZFS_TYPE_VOLUME;
			if (zfs_nicestrtonum(g_zfs, optarg, &intval) != 0) {
				(void) fprintf(stderr, gettext("bad volume "
				    "size '%s': %s\n"), optarg,
				    libzfs_error_description(g_zfs));
				goto error;
			}

			if (nvlist_add_uint64(props,
			    zfs_prop_to_name(ZFS_PROP_VOLSIZE), intval) != 0)
				nomem();
			volsize = intval;
			break;
		case 'p':
			parents = B_TRUE;
			break;
		case 'b':
			bflag = B_TRUE;
			if (zfs_nicestrtonum(g_zfs, optarg, &intval) != 0) {
				(void) fprintf(stderr, gettext("bad volume "
				    "block size '%s': %s\n"), optarg,
				    libzfs_error_description(g_zfs));
				goto error;
			}

			if (nvlist_add_uint64(props,
			    zfs_prop_to_name(ZFS_PROP_VOLBLOCKSIZE),
			    intval) != 0)
				nomem();
			break;
		case 'o':
			if (parseprop(props, optarg) != 0)
				goto error;
			break;
		case 's':
			noreserve = B_TRUE;
			break;
		case 'u':
			nomount = B_TRUE;
			break;
		case ':':
			(void) fprintf(stderr, gettext("missing size "
			    "argument\n"));
			goto badusage;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			goto badusage;
		}
	}

	if ((bflag || noreserve) && type != ZFS_TYPE_VOLUME) {
		(void) fprintf(stderr, gettext("'-s' and '-b' can only be "
		    "used when creating a volume\n"));
		goto badusage;
	}
	if (nomount && type != ZFS_TYPE_FILESYSTEM) {
		(void) fprintf(stderr, gettext("'-u' can only be "
		    "used when creating a file system\n"));
		goto badusage;
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc == 0) {
		(void) fprintf(stderr, gettext("missing %s argument\n"),
		    zfs_type_to_name(type));
		goto badusage;
	}
	if (argc > 1) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		goto badusage;
	}

	if (type == ZFS_TYPE_VOLUME && !noreserve) {
		zpool_handle_t *zpool_handle;
		nvlist_t *real_props = NULL;
		uint64_t spa_version;
		char *p;
		zfs_prop_t resv_prop;
		char *strval;
		char msg[1024];

		if ((p = strchr(argv[0], '/')) != NULL)
			*p = '\0';
		zpool_handle = zpool_open(g_zfs, argv[0]);
		if (p != NULL)
			*p = '/';
		if (zpool_handle == NULL)
			goto error;
		spa_version = zpool_get_prop_int(zpool_handle,
		    ZPOOL_PROP_VERSION, NULL);
		if (spa_version >= SPA_VERSION_REFRESERVATION)
			resv_prop = ZFS_PROP_REFRESERVATION;
		else
			resv_prop = ZFS_PROP_RESERVATION;

		(void) snprintf(msg, sizeof (msg),
		    gettext("cannot create '%s'"), argv[0]);
		if (props && (real_props = zfs_valid_proplist(g_zfs, type,
		    props, 0, NULL, zpool_handle, msg)) == NULL) {
			zpool_close(zpool_handle);
			goto error;
		}
		zpool_close(zpool_handle);

		volsize = zvol_volsize_to_reservation(volsize, real_props);
		nvlist_free(real_props);

		if (nvlist_lookup_string(props, zfs_prop_to_name(resv_prop),
		    &strval) != 0) {
			if (nvlist_add_uint64(props,
			    zfs_prop_to_name(resv_prop), volsize) != 0) {
				nvlist_free(props);
				nomem();
			}
		}
	}

	if (parents && zfs_name_valid(argv[0], type)) {
		/*
		 * Now create the ancestors of target dataset.  If the target
		 * already exists and '-p' option was used we should not
		 * complain.
		 */
		if (zfs_dataset_exists(g_zfs, argv[0], type)) {
			ret = 0;
			goto error;
		}
		if (zfs_create_ancestors(g_zfs, argv[0]) != 0)
			goto error;
	}

	/* pass to libzfs */
	if (zfs_create(g_zfs, argv[0], type, props) != 0)
		goto error;

	if ((zhp = zfs_open(g_zfs, argv[0], ZFS_TYPE_DATASET)) == NULL)
		goto error;

	ret = 0;

	/*
	 * Mount and/or share the new filesystem as appropriate.  We provide a
	 * verbose error message to let the user know that their filesystem was
	 * in fact created, even if we failed to mount or share it.
	 * If the user doesn't want the dataset automatically mounted,
	 * then skip the mount/share step altogether.
	 */
	if (!nomount && should_auto_mount(zhp)) {
		if (zfs_mount(zhp, NULL, 0) != 0) {
			(void) fprintf(stderr, gettext("filesystem "
			    "successfully created, but not mounted\n"));
			ret = 1;
		} else if (zfs_share(zhp) != 0) {
			(void) fprintf(stderr, gettext("filesystem "
			    "successfully created, but not shared\n"));
			ret = 1;
		}
	}

error:
	if (zhp)
		zfs_close(zhp);
	nvlist_free(props);
	return (ret);
badusage:
	nvlist_free(props);
	usage(B_FALSE);
	return (2);
}