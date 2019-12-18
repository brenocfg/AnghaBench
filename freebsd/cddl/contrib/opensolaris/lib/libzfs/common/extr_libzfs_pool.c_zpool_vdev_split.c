#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_15__ {int /*<<< orphan*/  zc_string; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int uint_t ;
typedef  int uint64_t ;
struct TYPE_16__ {int /*<<< orphan*/  import; scalar_t__ dryrun; } ;
typedef  TYPE_3__ splitflags_t ;
struct TYPE_17__ {void* create; void* import; } ;
typedef  TYPE_4__ prop_flags_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  EZFS_INVALCONFIG ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* VDEV_TYPE_HOLE ; 
 int /*<<< orphan*/  VDEV_TYPE_MIRROR ; 
 char* VDEV_TYPE_ROOT ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SPLIT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_HOLE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_LOG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int /*<<< orphan*/  ZPOOL_EXPORT_AFTER_SPLIT ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int find_vdev_entry (TYPE_1__*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 char* gettext (char*) ; 
 int no_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ nvlist_remove_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 
 scalar_t__ zcmd_write_conf_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zcmd_write_src_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** zfs_alloc (int /*<<< orphan*/ *,int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * zpool_get_config (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_name_valid (int /*<<< orphan*/ *,void*,char*) ; 
 int zpool_standard_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * zpool_valid_proplist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,TYPE_4__,char*) ; 

int
zpool_vdev_split(zpool_handle_t *zhp, char *newname, nvlist_t **newroot,
    nvlist_t *props, splitflags_t flags)
{
	zfs_cmd_t zc = { 0 };
	char msg[1024];
	nvlist_t *tree, *config, **child, **newchild, *newconfig = NULL;
	nvlist_t **varray = NULL, *zc_props = NULL;
	uint_t c, children, newchildren, lastlog = 0, vcount, found = 0;
	libzfs_handle_t *hdl = zhp->zpool_hdl;
	uint64_t vers;
	boolean_t freelist = B_FALSE, memory_err = B_TRUE;
	int retval = 0;

	(void) snprintf(msg, sizeof (msg),
	    dgettext(TEXT_DOMAIN, "Unable to split %s"), zhp->zpool_name);

	if (!zpool_name_valid(hdl, B_FALSE, newname))
		return (zfs_error(hdl, EZFS_INVALIDNAME, msg));

	if ((config = zpool_get_config(zhp, NULL)) == NULL) {
		(void) fprintf(stderr, gettext("Internal error: unable to "
		    "retrieve pool configuration\n"));
		return (-1);
	}

	verify(nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE, &tree)
	    == 0);
	verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_VERSION, &vers) == 0);

	if (props) {
		prop_flags_t flags = { .create = B_FALSE, .import = B_TRUE };
		if ((zc_props = zpool_valid_proplist(hdl, zhp->zpool_name,
		    props, vers, flags, msg)) == NULL)
			return (-1);
	}

	if (nvlist_lookup_nvlist_array(tree, ZPOOL_CONFIG_CHILDREN, &child,
	    &children) != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "Source pool is missing vdev tree"));
		nvlist_free(zc_props);
		return (-1);
	}

	varray = zfs_alloc(hdl, children * sizeof (nvlist_t *));
	vcount = 0;

	if (*newroot == NULL ||
	    nvlist_lookup_nvlist_array(*newroot, ZPOOL_CONFIG_CHILDREN,
	    &newchild, &newchildren) != 0)
		newchildren = 0;

	for (c = 0; c < children; c++) {
		uint64_t is_log = B_FALSE, is_hole = B_FALSE;
		char *type;
		nvlist_t **mchild, *vdev;
		uint_t mchildren;
		int entry;

		/*
		 * Unlike cache & spares, slogs are stored in the
		 * ZPOOL_CONFIG_CHILDREN array.  We filter them out here.
		 */
		(void) nvlist_lookup_uint64(child[c], ZPOOL_CONFIG_IS_LOG,
		    &is_log);
		(void) nvlist_lookup_uint64(child[c], ZPOOL_CONFIG_IS_HOLE,
		    &is_hole);
		if (is_log || is_hole) {
			/*
			 * Create a hole vdev and put it in the config.
			 */
			if (nvlist_alloc(&vdev, NV_UNIQUE_NAME, 0) != 0)
				goto out;
			if (nvlist_add_string(vdev, ZPOOL_CONFIG_TYPE,
			    VDEV_TYPE_HOLE) != 0)
				goto out;
			if (nvlist_add_uint64(vdev, ZPOOL_CONFIG_IS_HOLE,
			    1) != 0)
				goto out;
			if (lastlog == 0)
				lastlog = vcount;
			varray[vcount++] = vdev;
			continue;
		}
		lastlog = 0;
		verify(nvlist_lookup_string(child[c], ZPOOL_CONFIG_TYPE, &type)
		    == 0);
		if (strcmp(type, VDEV_TYPE_MIRROR) != 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Source pool must be composed only of mirrors\n"));
			retval = zfs_error(hdl, EZFS_INVALCONFIG, msg);
			goto out;
		}

		verify(nvlist_lookup_nvlist_array(child[c],
		    ZPOOL_CONFIG_CHILDREN, &mchild, &mchildren) == 0);

		/* find or add an entry for this top-level vdev */
		if (newchildren > 0 &&
		    (entry = find_vdev_entry(zhp, mchild, mchildren,
		    newchild, newchildren)) >= 0) {
			/* We found a disk that the user specified. */
			vdev = mchild[entry];
			++found;
		} else {
			/* User didn't specify a disk for this vdev. */
			vdev = mchild[mchildren - 1];
		}

		if (nvlist_dup(vdev, &varray[vcount++], 0) != 0)
			goto out;
	}

	/* did we find every disk the user specified? */
	if (found != newchildren) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "Device list must "
		    "include at most one disk from each mirror"));
		retval = zfs_error(hdl, EZFS_INVALCONFIG, msg);
		goto out;
	}

	/* Prepare the nvlist for populating. */
	if (*newroot == NULL) {
		if (nvlist_alloc(newroot, NV_UNIQUE_NAME, 0) != 0)
			goto out;
		freelist = B_TRUE;
		if (nvlist_add_string(*newroot, ZPOOL_CONFIG_TYPE,
		    VDEV_TYPE_ROOT) != 0)
			goto out;
	} else {
		verify(nvlist_remove_all(*newroot, ZPOOL_CONFIG_CHILDREN) == 0);
	}

	/* Add all the children we found */
	if (nvlist_add_nvlist_array(*newroot, ZPOOL_CONFIG_CHILDREN, varray,
	    lastlog == 0 ? vcount : lastlog) != 0)
		goto out;

	/*
	 * If we're just doing a dry run, exit now with success.
	 */
	if (flags.dryrun) {
		memory_err = B_FALSE;
		freelist = B_FALSE;
		goto out;
	}

	/* now build up the config list & call the ioctl */
	if (nvlist_alloc(&newconfig, NV_UNIQUE_NAME, 0) != 0)
		goto out;

	if (nvlist_add_nvlist(newconfig,
	    ZPOOL_CONFIG_VDEV_TREE, *newroot) != 0 ||
	    nvlist_add_string(newconfig,
	    ZPOOL_CONFIG_POOL_NAME, newname) != 0 ||
	    nvlist_add_uint64(newconfig, ZPOOL_CONFIG_VERSION, vers) != 0)
		goto out;

	/*
	 * The new pool is automatically part of the namespace unless we
	 * explicitly export it.
	 */
	if (!flags.import)
		zc.zc_cookie = ZPOOL_EXPORT_AFTER_SPLIT;
	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	(void) strlcpy(zc.zc_string, newname, sizeof (zc.zc_string));
	if (zcmd_write_conf_nvlist(hdl, &zc, newconfig) != 0)
		goto out;
	if (zc_props != NULL && zcmd_write_src_nvlist(hdl, &zc, zc_props) != 0)
		goto out;

	if (zfs_ioctl(hdl, ZFS_IOC_VDEV_SPLIT, &zc) != 0) {
		retval = zpool_standard_error(hdl, errno, msg);
		goto out;
	}

	freelist = B_FALSE;
	memory_err = B_FALSE;

out:
	if (varray != NULL) {
		int v;

		for (v = 0; v < vcount; v++)
			nvlist_free(varray[v]);
		free(varray);
	}
	zcmd_free_nvlists(&zc);
	nvlist_free(zc_props);
	nvlist_free(newconfig);
	if (freelist) {
		nvlist_free(*newroot);
		*newroot = NULL;
	}

	if (retval != 0)
		return (retval);

	if (memory_err)
		return (no_memory(hdl));

	return (0);
}