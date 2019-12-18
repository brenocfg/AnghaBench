#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int (* zfs_iter_f ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  libzfs_ns_avl; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  cn_name; } ;
typedef  TYPE_2__ config_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * make_dataset_handle (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ namespace_reload (TYPE_1__*) ; 
 TYPE_2__* uu_avl_first (int /*<<< orphan*/ ) ; 
 TYPE_2__* uu_avl_next (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ zpool_skip_pool (int /*<<< orphan*/ ) ; 

int
zfs_iter_root(libzfs_handle_t *hdl, zfs_iter_f func, void *data)
{
	config_node_t *cn;
	zfs_handle_t *zhp;
	int ret;

	if (namespace_reload(hdl) != 0)
		return (-1);

	for (cn = uu_avl_first(hdl->libzfs_ns_avl); cn != NULL;
	    cn = uu_avl_next(hdl->libzfs_ns_avl, cn)) {

		if (zpool_skip_pool(cn->cn_name))
			continue;

		if ((zhp = make_dataset_handle(hdl, cn->cn_name)) == NULL)
			continue;

		if ((ret = func(zhp, data)) != 0)
			return (ret);
	}

	return (0);
}