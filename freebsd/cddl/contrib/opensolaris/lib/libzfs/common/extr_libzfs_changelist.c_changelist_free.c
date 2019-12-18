#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cl_pool; scalar_t__ cl_list; int /*<<< orphan*/  cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
typedef  TYPE_1__ prop_changelist_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  uu_list_destroy (scalar_t__) ; 
 int /*<<< orphan*/  uu_list_pool_destroy (scalar_t__) ; 
 TYPE_1__* uu_list_teardown (scalar_t__,void**) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ ) ; 

void
changelist_free(prop_changelist_t *clp)
{
	prop_changenode_t *cn;
	void *cookie;

	if (clp->cl_list) {
		cookie = NULL;
		while ((cn = uu_list_teardown(clp->cl_list, &cookie)) != NULL) {
			zfs_close(cn->cn_handle);
			free(cn);
		}

		uu_list_destroy(clp->cl_list);
	}
	if (clp->cl_pool)
		uu_list_pool_destroy(clp->cl_pool);

	free(clp);
}