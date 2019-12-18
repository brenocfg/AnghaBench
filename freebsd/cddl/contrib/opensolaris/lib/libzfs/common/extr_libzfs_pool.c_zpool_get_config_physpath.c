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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int EZFS_INVALCONFIG ; 
 int EZFS_NODEVICE ; 
 int EZFS_POOL_INVALARG ; 
 int /*<<< orphan*/  VDEV_TYPE_ROOT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_get_physpaths (int /*<<< orphan*/ *,char*,size_t,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zpool_get_config_physpath(nvlist_t *config, char *physpath, size_t phypath_size)
{
	size_t rsz;
	nvlist_t *vdev_root;
	nvlist_t **child;
	uint_t count;
	char *type;

	rsz = 0;

	if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
	    &vdev_root) != 0)
		return (EZFS_INVALCONFIG);

	if (nvlist_lookup_string(vdev_root, ZPOOL_CONFIG_TYPE, &type) != 0 ||
	    nvlist_lookup_nvlist_array(vdev_root, ZPOOL_CONFIG_CHILDREN,
	    &child, &count) != 0)
		return (EZFS_INVALCONFIG);

	/*
	 * root pool can only have a single top-level vdev.
	 */
	if (strcmp(type, VDEV_TYPE_ROOT) != 0 || count != 1)
		return (EZFS_POOL_INVALARG);

	(void) vdev_get_physpaths(child[0], physpath, phypath_size, &rsz,
	    B_FALSE);

	/* No online devices */
	if (rsz == 0)
		return (EZFS_NODEVICE);

	return (0);
}