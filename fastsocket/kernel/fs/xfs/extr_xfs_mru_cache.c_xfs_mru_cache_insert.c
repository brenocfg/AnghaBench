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
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  store; scalar_t__ lists; } ;
typedef  TYPE_1__ xfs_mru_cache_t ;
struct TYPE_10__ {unsigned long key; void* value; int /*<<< orphan*/  list_node; } ;
typedef  TYPE_2__ xfs_mru_cache_elem_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  _xfs_mru_cache_list_insert (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,unsigned long,TYPE_2__*) ; 
 scalar_t__ radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_mru_elem_zone ; 

int
xfs_mru_cache_insert(
	xfs_mru_cache_t	*mru,
	unsigned long	key,
	void		*value)
{
	xfs_mru_cache_elem_t *elem;

	ASSERT(mru && mru->lists);
	if (!mru || !mru->lists)
		return EINVAL;

	elem = kmem_zone_zalloc(xfs_mru_elem_zone, KM_SLEEP);
	if (!elem)
		return ENOMEM;

	if (radix_tree_preload(GFP_KERNEL)) {
		kmem_zone_free(xfs_mru_elem_zone, elem);
		return ENOMEM;
	}

	INIT_LIST_HEAD(&elem->list_node);
	elem->key = key;
	elem->value = value;

	spin_lock(&mru->lock);

	radix_tree_insert(&mru->store, key, elem);
	radix_tree_preload_end();
	_xfs_mru_cache_list_insert(mru, elem);

	spin_unlock(&mru->lock);

	return 0;
}