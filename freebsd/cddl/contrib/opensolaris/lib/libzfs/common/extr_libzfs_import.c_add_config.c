#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ve_guid; TYPE_5__* ve_configs; struct TYPE_8__* ve_next; } ;
typedef  TYPE_1__ vdev_entry_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {TYPE_4__* names; TYPE_3__* pools; } ;
typedef  TYPE_2__ pool_list_t ;
struct TYPE_10__ {scalar_t__ pe_guid; TYPE_1__* pe_vdevs; struct TYPE_10__* pe_next; } ;
typedef  TYPE_3__ pool_entry_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_11__ {struct TYPE_11__* ne_next; scalar_t__ ne_guid; int /*<<< orphan*/ * ne_name; } ;
typedef  TYPE_4__ name_entry_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
struct TYPE_12__ {scalar_t__ ce_txg; struct TYPE_12__* ce_next; int /*<<< orphan*/  ce_config; } ;
typedef  TYPE_5__ config_entry_t ;

/* Variables and functions */
 scalar_t__ POOL_STATE_L2CACHE ; 
 scalar_t__ POOL_STATE_SPARE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_TXG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TOP_GUID ; 
 int /*<<< orphan*/  fnvlist_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 void* zfs_alloc (int /*<<< orphan*/ *,int) ; 
 void* zfs_strdup (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
add_config(libzfs_handle_t *hdl, pool_list_t *pl, const char *path,
    nvlist_t *config)
{
	uint64_t pool_guid, vdev_guid, top_guid, txg, state;
	pool_entry_t *pe;
	vdev_entry_t *ve;
	config_entry_t *ce;
	name_entry_t *ne;

	/*
	 * If this is a hot spare not currently in use or level 2 cache
	 * device, add it to the list of names to translate, but don't do
	 * anything else.
	 */
	if (nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_STATE,
	    &state) == 0 &&
	    (state == POOL_STATE_SPARE || state == POOL_STATE_L2CACHE) &&
	    nvlist_lookup_uint64(config, ZPOOL_CONFIG_GUID, &vdev_guid) == 0) {
		if ((ne = zfs_alloc(hdl, sizeof (name_entry_t))) == NULL)
			return (-1);

		if ((ne->ne_name = zfs_strdup(hdl, path)) == NULL) {
			free(ne);
			return (-1);
		}

		ne->ne_guid = vdev_guid;
		ne->ne_next = pl->names;
		pl->names = ne;

		return (0);
	}

	/*
	 * If we have a valid config but cannot read any of these fields, then
	 * it means we have a half-initialized label.  In vdev_label_init()
	 * we write a label with txg == 0 so that we can identify the device
	 * in case the user refers to the same disk later on.  If we fail to
	 * create the pool, we'll be left with a label in this state
	 * which should not be considered part of a valid pool.
	 */
	if (nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_GUID,
	    &pool_guid) != 0 ||
	    nvlist_lookup_uint64(config, ZPOOL_CONFIG_GUID,
	    &vdev_guid) != 0 ||
	    nvlist_lookup_uint64(config, ZPOOL_CONFIG_TOP_GUID,
	    &top_guid) != 0 ||
	    nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_TXG,
	    &txg) != 0 || txg == 0) {
		return (0);
	}

	/*
	 * First, see if we know about this pool.  If not, then add it to the
	 * list of known pools.
	 */
	for (pe = pl->pools; pe != NULL; pe = pe->pe_next) {
		if (pe->pe_guid == pool_guid)
			break;
	}

	if (pe == NULL) {
		if ((pe = zfs_alloc(hdl, sizeof (pool_entry_t))) == NULL) {
			return (-1);
		}
		pe->pe_guid = pool_guid;
		pe->pe_next = pl->pools;
		pl->pools = pe;
	}

	/*
	 * Second, see if we know about this toplevel vdev.  Add it if its
	 * missing.
	 */
	for (ve = pe->pe_vdevs; ve != NULL; ve = ve->ve_next) {
		if (ve->ve_guid == top_guid)
			break;
	}

	if (ve == NULL) {
		if ((ve = zfs_alloc(hdl, sizeof (vdev_entry_t))) == NULL) {
			return (-1);
		}
		ve->ve_guid = top_guid;
		ve->ve_next = pe->pe_vdevs;
		pe->pe_vdevs = ve;
	}

	/*
	 * Third, see if we have a config with a matching transaction group.  If
	 * so, then we do nothing.  Otherwise, add it to the list of known
	 * configs.
	 */
	for (ce = ve->ve_configs; ce != NULL; ce = ce->ce_next) {
		if (ce->ce_txg == txg)
			break;
	}

	if (ce == NULL) {
		if ((ce = zfs_alloc(hdl, sizeof (config_entry_t))) == NULL) {
			return (-1);
		}
		ce->ce_txg = txg;
		ce->ce_config = fnvlist_dup(config);
		ce->ce_next = ve->ve_configs;
		ve->ve_configs = ce;
	}

	/*
	 * At this point we've successfully added our config to the list of
	 * known configs.  The last thing to do is add the vdev guid -> path
	 * mappings so that we can fix up the configuration as necessary before
	 * doing the import.
	 */
	if ((ne = zfs_alloc(hdl, sizeof (name_entry_t))) == NULL)
		return (-1);

	if ((ne->ne_name = zfs_strdup(hdl, path)) == NULL) {
		free(ne);
		return (-1);
	}

	ne->ne_guid = vdev_guid;
	ne->ne_next = pl->names;
	pl->names = ne;

	return (0);
}