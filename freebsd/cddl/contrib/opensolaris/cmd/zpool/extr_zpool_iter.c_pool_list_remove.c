#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * zn_handle; } ;
typedef  TYPE_1__ zpool_node_t ;
struct TYPE_9__ {int /*<<< orphan*/  zl_avl; } ;
typedef  TYPE_2__ zpool_list_t ;
typedef  int /*<<< orphan*/  zpool_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* uu_avl_find (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_avl_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 

void
pool_list_remove(zpool_list_t *zlp, zpool_handle_t *zhp)
{
	zpool_node_t search, *node;

	search.zn_handle = zhp;
	if ((node = uu_avl_find(zlp->zl_avl, &search, NULL, NULL)) != NULL) {
		uu_avl_remove(zlp->zl_avl, node);
		zpool_close(node->zn_handle);
		free(node);
	}
}