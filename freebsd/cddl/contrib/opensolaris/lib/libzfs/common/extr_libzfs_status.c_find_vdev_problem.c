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
typedef  int /*<<< orphan*/  vdev_stat_t ;
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  VDEV_TYPE_REPLACING ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_STATS ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 

__attribute__((used)) static boolean_t
find_vdev_problem(nvlist_t *vdev, int (*func)(vdev_stat_t *, uint_t),
    boolean_t ignore_replacing)
{
	nvlist_t **child;
	vdev_stat_t *vs;
	uint_t c, vsc, children;

	/*
	 * Ignore problems within a 'replacing' vdev, since we're presumably in
	 * the process of repairing any such errors, and don't want to call them
	 * out again.  We'll pick up the fact that a resilver is happening
	 * later.
	 */
	if (ignore_replacing == B_TRUE) {
		char *type;

		verify(nvlist_lookup_string(vdev, ZPOOL_CONFIG_TYPE,
		    &type) == 0);
		if (strcmp(type, VDEV_TYPE_REPLACING) == 0)
			return (B_FALSE);
	}

	if (nvlist_lookup_nvlist_array(vdev, ZPOOL_CONFIG_CHILDREN, &child,
	    &children) == 0) {
		for (c = 0; c < children; c++)
			if (find_vdev_problem(child[c], func, ignore_replacing))
				return (B_TRUE);
	} else {
		verify(nvlist_lookup_uint64_array(vdev, ZPOOL_CONFIG_VDEV_STATS,
		    (uint64_t **)&vs, &vsc) == 0);

		if (func(vs, vsc) != 0)
			return (B_TRUE);
	}

	/*
	 * Check any L2 cache devs
	 */
	if (nvlist_lookup_nvlist_array(vdev, ZPOOL_CONFIG_L2CACHE, &child,
	    &children) == 0) {
		for (c = 0; c < children; c++)
			if (find_vdev_problem(child[c], func, ignore_replacing))
				return (B_TRUE);
	}

	return (B_FALSE);
}