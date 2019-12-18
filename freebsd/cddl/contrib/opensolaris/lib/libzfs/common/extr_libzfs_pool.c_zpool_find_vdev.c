#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zpool_config; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 char* _PATH_DEV ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ strtoull (char const*,char**,int) ; 
 int /*<<< orphan*/ * vdev_to_nvlist_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zpool_vdev_is_interior (char const*) ; 

nvlist_t *
zpool_find_vdev(zpool_handle_t *zhp, const char *path, boolean_t *avail_spare,
    boolean_t *l2cache, boolean_t *log)
{
	char buf[MAXPATHLEN];
	char *end;
	nvlist_t *nvroot, *search, *ret;
	uint64_t guid;

	verify(nvlist_alloc(&search, NV_UNIQUE_NAME, KM_SLEEP) == 0);

	guid = strtoull(path, &end, 10);
	if (guid != 0 && *end == '\0') {
		verify(nvlist_add_uint64(search, ZPOOL_CONFIG_GUID, guid) == 0);
	} else if (zpool_vdev_is_interior(path)) {
		verify(nvlist_add_string(search, ZPOOL_CONFIG_TYPE, path) == 0);
	} else if (path[0] != '/') {
		(void) snprintf(buf, sizeof (buf), "%s%s", _PATH_DEV, path);
		verify(nvlist_add_string(search, ZPOOL_CONFIG_PATH, buf) == 0);
	} else {
		verify(nvlist_add_string(search, ZPOOL_CONFIG_PATH, path) == 0);
	}

	verify(nvlist_lookup_nvlist(zhp->zpool_config, ZPOOL_CONFIG_VDEV_TREE,
	    &nvroot) == 0);

	*avail_spare = B_FALSE;
	*l2cache = B_FALSE;
	if (log != NULL)
		*log = B_FALSE;
	ret = vdev_to_nvlist_iter(nvroot, search, avail_spare, l2cache, log);
	nvlist_free(search);

	return (ret);
}