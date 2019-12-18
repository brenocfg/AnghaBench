#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zn_avlnode; int /*<<< orphan*/ * zn_handle; } ;
typedef  TYPE_1__ zfs_node_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  uu_avl_index_t ;
struct TYPE_11__ {int cb_types; int cb_flags; scalar_t__ cb_depth; scalar_t__ cb_depth_limit; int /*<<< orphan*/  cb_avl; TYPE_4__** cb_proplist; int /*<<< orphan*/  cb_props_table; int /*<<< orphan*/  cb_sortcol; } ;
typedef  TYPE_2__ callback_data_t ;
typedef  int boolean_t ;
struct TYPE_12__ {int /*<<< orphan*/  pl_all; } ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 int ZFS_ITER_DEPTH_LIMIT ; 
 int ZFS_ITER_LITERAL_PROPS ; 
 int ZFS_ITER_RECURSE ; 
 int ZFS_ITER_RECVD_PROPS ; 
 int ZFS_ITER_SIMPLE ; 
 int ZFS_TYPE_BOOKMARK ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  avl_pool ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* safe_malloc (int) ; 
 int /*<<< orphan*/ * uu_avl_find (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_avl_insert (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_avl_node_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_expand_proplist (int /*<<< orphan*/ *,TYPE_4__**,int,int) ; 
 int zfs_get_type (int /*<<< orphan*/ *) ; 
 int zfs_include_snapshots (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_iter_bookmarks (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 
 int /*<<< orphan*/  zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 
 int /*<<< orphan*/  zfs_iter_snapshots (int /*<<< orphan*/ *,int,int (*) (int /*<<< orphan*/ *,void*),void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prune_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_callback(zfs_handle_t *zhp, void *data)
{
	callback_data_t *cb = data;
	boolean_t should_close = B_TRUE;
	boolean_t include_snaps = zfs_include_snapshots(zhp, cb);
	boolean_t include_bmarks = (cb->cb_types & ZFS_TYPE_BOOKMARK);

	if ((zfs_get_type(zhp) & cb->cb_types) ||
	    ((zfs_get_type(zhp) == ZFS_TYPE_SNAPSHOT) && include_snaps)) {
		uu_avl_index_t idx;
		zfs_node_t *node = safe_malloc(sizeof (zfs_node_t));

		node->zn_handle = zhp;
		uu_avl_node_init(node, &node->zn_avlnode, avl_pool);
		if (uu_avl_find(cb->cb_avl, node, cb->cb_sortcol,
		    &idx) == NULL) {
			if (cb->cb_proplist) {
				if ((*cb->cb_proplist) &&
				    !(*cb->cb_proplist)->pl_all)
					zfs_prune_proplist(zhp,
					    cb->cb_props_table);

				if (zfs_expand_proplist(zhp, cb->cb_proplist,
				    (cb->cb_flags & ZFS_ITER_RECVD_PROPS),
				    (cb->cb_flags & ZFS_ITER_LITERAL_PROPS))
				    != 0) {
					free(node);
					return (-1);
				}
			}
			uu_avl_insert(cb->cb_avl, node, idx);
			should_close = B_FALSE;
		} else {
			free(node);
		}
	}

	/*
	 * Recurse if necessary.
	 */
	if (cb->cb_flags & ZFS_ITER_RECURSE &&
	    ((cb->cb_flags & ZFS_ITER_DEPTH_LIMIT) == 0 ||
	    cb->cb_depth < cb->cb_depth_limit)) {
		cb->cb_depth++;
		if (zfs_get_type(zhp) == ZFS_TYPE_FILESYSTEM)
			(void) zfs_iter_filesystems(zhp, zfs_callback, data);
		if (((zfs_get_type(zhp) & (ZFS_TYPE_SNAPSHOT |
		    ZFS_TYPE_BOOKMARK)) == 0) && include_snaps)
			(void) zfs_iter_snapshots(zhp,
			    (cb->cb_flags & ZFS_ITER_SIMPLE) != 0, zfs_callback,
			    data, 0, 0);
		if (((zfs_get_type(zhp) & (ZFS_TYPE_SNAPSHOT |
		    ZFS_TYPE_BOOKMARK)) == 0) && include_bmarks)
			(void) zfs_iter_bookmarks(zhp, zfs_callback, data);
		cb->cb_depth--;
	}

	if (should_close)
		zfs_close(zhp);

	return (0);
}