#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* pl_next; int /*<<< orphan*/  pl_all; int /*<<< orphan*/  pl_fixed; int /*<<< orphan*/  pl_prop; int /*<<< orphan*/  pl_width; } ;
typedef  TYPE_1__ zprop_list_t ;
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * hdl; TYPE_1__** last; } ;
typedef  TYPE_2__ expand_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZFS_PROP_NAME ; 
 int /*<<< orphan*/  ZFS_TYPE_POOL ; 
 int /*<<< orphan*/  ZPOOL_PROP_NAME ; 
 scalar_t__ ZPROP_INVAL ; 
 TYPE_1__* zfs_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zprop_expand_list_cb ; 
 scalar_t__ zprop_iter_common (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprop_width (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zprop_expand_list(libzfs_handle_t *hdl, zprop_list_t **plp, zfs_type_t type)
{
	zprop_list_t *entry;
	zprop_list_t **last;
	expand_data_t exp;

	if (*plp == NULL) {
		/*
		 * If this is the very first time we've been called for an 'all'
		 * specification, expand the list to include all native
		 * properties.
		 */
		last = plp;

		exp.last = last;
		exp.hdl = hdl;
		exp.type = type;

		if (zprop_iter_common(zprop_expand_list_cb, &exp, B_FALSE,
		    B_FALSE, type) == ZPROP_INVAL)
			return (-1);

		/*
		 * Add 'name' to the beginning of the list, which is handled
		 * specially.
		 */
		if ((entry = zfs_alloc(hdl, sizeof (zprop_list_t))) == NULL)
			return (-1);

		entry->pl_prop = (type == ZFS_TYPE_POOL) ?  ZPOOL_PROP_NAME :
		    ZFS_PROP_NAME;
		entry->pl_width = zprop_width(entry->pl_prop,
		    &entry->pl_fixed, type);
		entry->pl_all = B_TRUE;
		entry->pl_next = *plp;
		*plp = entry;
	}
	return (0);
}