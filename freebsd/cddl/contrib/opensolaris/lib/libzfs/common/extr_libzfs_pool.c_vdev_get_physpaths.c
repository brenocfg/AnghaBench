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
typedef  int uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int EZFS_INVALCONFIG ; 
 int EZFS_NOSPC ; 
 int EZFS_POOL_INVALARG ; 
 int /*<<< orphan*/  VDEV_TYPE_DISK ; 
 int /*<<< orphan*/  VDEV_TYPE_MIRROR ; 
 int /*<<< orphan*/  VDEV_TYPE_RAIDZ ; 
 int /*<<< orphan*/  VDEV_TYPE_REPLACING ; 
 int /*<<< orphan*/  VDEV_TYPE_SPARE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_SPARE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int vdev_get_one_physpath (int /*<<< orphan*/ *,char*,size_t,size_t*) ; 
 scalar_t__ vdev_online (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vdev_get_physpaths(nvlist_t *nv, char *physpath, size_t phypath_size,
    size_t *rsz, boolean_t is_spare)
{
	char *type;
	int ret;

	if (nvlist_lookup_string(nv, ZPOOL_CONFIG_TYPE, &type) != 0)
		return (EZFS_INVALCONFIG);

	if (strcmp(type, VDEV_TYPE_DISK) == 0) {
		/*
		 * An active spare device has ZPOOL_CONFIG_IS_SPARE set.
		 * For a spare vdev, we only want to boot from the active
		 * spare device.
		 */
		if (is_spare) {
			uint64_t spare = 0;
			(void) nvlist_lookup_uint64(nv, ZPOOL_CONFIG_IS_SPARE,
			    &spare);
			if (!spare)
				return (EZFS_INVALCONFIG);
		}

		if (vdev_online(nv)) {
			if ((ret = vdev_get_one_physpath(nv, physpath,
			    phypath_size, rsz)) != 0)
				return (ret);
		}
	} else if (strcmp(type, VDEV_TYPE_MIRROR) == 0 ||
	    strcmp(type, VDEV_TYPE_RAIDZ) == 0 ||
	    strcmp(type, VDEV_TYPE_REPLACING) == 0 ||
	    (is_spare = (strcmp(type, VDEV_TYPE_SPARE) == 0))) {
		nvlist_t **child;
		uint_t count;
		int i, ret;

		if (nvlist_lookup_nvlist_array(nv,
		    ZPOOL_CONFIG_CHILDREN, &child, &count) != 0)
			return (EZFS_INVALCONFIG);

		for (i = 0; i < count; i++) {
			ret = vdev_get_physpaths(child[i], physpath,
			    phypath_size, rsz, is_spare);
			if (ret == EZFS_NOSPC)
				return (ret);
		}
	}

	return (EZFS_POOL_INVALARG);
}