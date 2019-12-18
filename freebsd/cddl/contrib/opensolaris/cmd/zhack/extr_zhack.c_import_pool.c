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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;
struct TYPE_3__ {char const* poolname; void* can_be_active; void* unique; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int EEXIST ; 
 int FREAD ; 
 int /*<<< orphan*/  FTAG ; 
 int FWRITE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZFS_IMPORT_NORMAL ; 
 int /*<<< orphan*/  ZPOOL_PROP_READONLY ; 
 int /*<<< orphan*/  dmu_objset_register_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,...) ; 
 TYPE_1__ g_importargs ; 
 char const* g_pool ; 
 void* g_readonly ; 
 int /*<<< orphan*/ * g_zfs ; 
 int /*<<< orphan*/  kernel_init (int) ; 
 int /*<<< orphan*/ * libzfs_init () ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_import (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_open (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  space_delta_cb ; 
 char* strdup (char const*) ; 
 char const* strerror (int) ; 
 char* strpbrk (char const*,char*) ; 
 int /*<<< orphan*/  verify (int) ; 
 void* zfeature_checks_disable ; 
 int /*<<< orphan*/  zpool_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zpool_search_import (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
import_pool(const char *target, boolean_t readonly)
{
	nvlist_t *config;
	nvlist_t *pools;
	int error;
	char *sepp;
	spa_t *spa;
	nvpair_t *elem;
	nvlist_t *props;
	const char *name;

	kernel_init(readonly ? FREAD : (FREAD | FWRITE));
	g_zfs = libzfs_init();
	ASSERT(g_zfs != NULL);

	dmu_objset_register_type(DMU_OST_ZFS, space_delta_cb);

	g_readonly = readonly;

	/*
	 * If we only want readonly access, it's OK if we find
	 * a potentially-active (ie, imported into the kernel) pool from the
	 * default cachefile.
	 */
	if (readonly && spa_open(target, &spa, FTAG) == 0) {
		spa_close(spa, FTAG);
		return;
	}

	g_importargs.unique = B_TRUE;
	g_importargs.can_be_active = readonly;
	g_pool = strdup(target);
	if ((sepp = strpbrk(g_pool, "/@")) != NULL)
		*sepp = '\0';
	g_importargs.poolname = g_pool;
	pools = zpool_search_import(g_zfs, &g_importargs);

	if (nvlist_empty(pools)) {
		if (!g_importargs.can_be_active) {
			g_importargs.can_be_active = B_TRUE;
			if (zpool_search_import(g_zfs, &g_importargs) != NULL ||
			    spa_open(target, &spa, FTAG) == 0) {
				fatal(spa, FTAG, "cannot import '%s': pool is "
				    "active; run " "\"zpool export %s\" "
				    "first\n", g_pool, g_pool);
			}
		}

		fatal(NULL, FTAG, "cannot import '%s': no such pool "
		    "available\n", g_pool);
	}

	elem = nvlist_next_nvpair(pools, NULL);
	name = nvpair_name(elem);
	verify(nvpair_value_nvlist(elem, &config) == 0);

	props = NULL;
	if (readonly) {
		verify(nvlist_alloc(&props, NV_UNIQUE_NAME, 0) == 0);
		verify(nvlist_add_uint64(props,
		    zpool_prop_to_name(ZPOOL_PROP_READONLY), 1) == 0);
	}

	zfeature_checks_disable = B_TRUE;
	error = spa_import(name, config, props, ZFS_IMPORT_NORMAL);
	zfeature_checks_disable = B_FALSE;
	if (error == EEXIST)
		error = 0;

	if (error)
		fatal(NULL, FTAG, "can't import '%s': %s", name,
		    strerror(error));
}