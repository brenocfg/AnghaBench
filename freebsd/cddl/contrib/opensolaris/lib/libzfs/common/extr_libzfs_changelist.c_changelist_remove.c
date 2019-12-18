#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
struct TYPE_11__ {int /*<<< orphan*/  cl_list; } ;
typedef  TYPE_2__ prop_changelist_t ;
struct TYPE_12__ {int /*<<< orphan*/  zfs_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* uu_list_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* uu_list_next (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uu_list_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_close (TYPE_3__*) ; 

void
changelist_remove(prop_changelist_t *clp, const char *name)
{
	prop_changenode_t *cn;

	for (cn = uu_list_first(clp->cl_list); cn != NULL;
	    cn = uu_list_next(clp->cl_list, cn)) {

		if (strcmp(cn->cn_handle->zfs_name, name) == 0) {
			uu_list_remove(clp->cl_list, cn);
			zfs_close(cn->cn_handle);
			free(cn);
			return;
		}
	}
}