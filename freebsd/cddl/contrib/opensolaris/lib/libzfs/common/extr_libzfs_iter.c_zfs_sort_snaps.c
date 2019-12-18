#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* zn_handle; } ;
typedef  TYPE_1__ zfs_node_t ;
struct TYPE_12__ {int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_2__ zfs_handle_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* zfs_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_close (TYPE_2__*) ; 

__attribute__((used)) static int
zfs_sort_snaps(zfs_handle_t *zhp, void *data)
{
	avl_tree_t *avl = data;
	zfs_node_t *node;
	zfs_node_t search;

	search.zn_handle = zhp;
	node = avl_find(avl, &search, NULL);
	if (node) {
		/*
		 * If this snapshot was renamed while we were creating the
		 * AVL tree, it's possible that we already inserted it under
		 * its old name. Remove the old handle before adding the new
		 * one.
		 */
		zfs_close(node->zn_handle);
		avl_remove(avl, node);
		free(node);
	}

	node = zfs_alloc(zhp->zfs_hdl, sizeof (zfs_node_t));
	node->zn_handle = zhp;
	avl_add(avl, node);

	return (0);
}