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
typedef  size_t uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  VDEV_TYPE_DISK ; 
 int /*<<< orphan*/  VDEV_TYPE_FILE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_WHOLE_DISK ; 
 int check_device (char*,int,int) ; 
 int check_file (char*,int,int) ; 
 scalar_t__ is_spare (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  verify (int) ; 

__attribute__((used)) static boolean_t
is_device_in_use(nvlist_t *config, nvlist_t *nv, boolean_t force,
    boolean_t replacing, boolean_t isspare)
{
	nvlist_t **child;
	uint_t c, children;
	char *type, *path;
	int ret = 0;
	char buf[MAXPATHLEN];
	uint64_t wholedisk;
	boolean_t anyinuse = B_FALSE;

	verify(nvlist_lookup_string(nv, ZPOOL_CONFIG_TYPE, &type) == 0);

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_CHILDREN,
	    &child, &children) != 0) {

		verify(nvlist_lookup_string(nv, ZPOOL_CONFIG_PATH, &path) == 0);

		/*
		 * As a generic check, we look to see if this is a replace of a
		 * hot spare within the same pool.  If so, we allow it
		 * regardless of what libdiskmgt or zpool_in_use() says.
		 */
		if (replacing) {
#ifdef illumos
			if (nvlist_lookup_uint64(nv, ZPOOL_CONFIG_WHOLE_DISK,
			    &wholedisk) == 0 && wholedisk)
				(void) snprintf(buf, sizeof (buf), "%ss0",
				    path);
			else
#endif
				(void) strlcpy(buf, path, sizeof (buf));

			if (is_spare(config, buf))
				return (B_FALSE);
		}

		if (strcmp(type, VDEV_TYPE_DISK) == 0)
			ret = check_device(path, force, isspare);
		else if (strcmp(type, VDEV_TYPE_FILE) == 0)
			ret = check_file(path, force, isspare);

		return (ret != 0);
	}

	for (c = 0; c < children; c++)
		if (is_device_in_use(config, child[c], force, replacing,
		    B_FALSE))
			anyinuse = B_TRUE;

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_SPARES,
	    &child, &children) == 0)
		for (c = 0; c < children; c++)
			if (is_device_in_use(config, child[c], force, replacing,
			    B_TRUE))
				anyinuse = B_TRUE;

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_L2CACHE,
	    &child, &children) == 0)
		for (c = 0; c < children; c++)
			if (is_device_in_use(config, child[c], force, replacing,
			    B_FALSE))
				anyinuse = B_TRUE;

	return (anyinuse);
}