#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  store; scalar_t__ lists; } ;
typedef  TYPE_1__ xfs_mru_cache_t ;
struct TYPE_8__ {void* value; int /*<<< orphan*/  list_node; } ;
typedef  TYPE_2__ xfs_mru_cache_elem_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _xfs_mru_cache_list_insert (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mru_lock ; 
 TYPE_2__* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void *
xfs_mru_cache_lookup(
	xfs_mru_cache_t	*mru,
	unsigned long	key)
{
	xfs_mru_cache_elem_t *elem;

	ASSERT(mru && mru->lists);
	if (!mru || !mru->lists)
		return NULL;

	spin_lock(&mru->lock);
	elem = radix_tree_lookup(&mru->store, key);
	if (elem) {
		list_del(&elem->list_node);
		_xfs_mru_cache_list_insert(mru, elem);
		__release(mru_lock); /* help sparse not be stupid */
	} else
		spin_unlock(&mru->lock);

	return elem ? elem->value : NULL;
}