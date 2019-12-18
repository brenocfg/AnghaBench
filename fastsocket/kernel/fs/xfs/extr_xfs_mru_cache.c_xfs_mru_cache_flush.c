#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int grp_count; int grp_time; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; scalar_t__ queued; int /*<<< orphan*/  lists; } ;
typedef  TYPE_1__ xfs_mru_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  _xfs_mru_cache_clear_reap_list (TYPE_1__*) ; 
 int /*<<< orphan*/  _xfs_mru_cache_migrate (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfs_mru_cache_flush(
	xfs_mru_cache_t		*mru)
{
	if (!mru || !mru->lists)
		return;

	spin_lock(&mru->lock);
	if (mru->queued) {
		spin_unlock(&mru->lock);
		cancel_delayed_work_sync(&mru->work);
		spin_lock(&mru->lock);
	}

	_xfs_mru_cache_migrate(mru, jiffies + mru->grp_count * mru->grp_time);
	_xfs_mru_cache_clear_reap_list(mru);

	spin_unlock(&mru->lock);
}