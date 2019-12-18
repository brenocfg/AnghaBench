#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gfs2_quota_data {int /*<<< orphan*/  qd_reclaim; int /*<<< orphan*/  qd_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qd_lru_count ; 
 int /*<<< orphan*/  qd_lru_list ; 
 int /*<<< orphan*/  qd_lru_lock ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qd_put(struct gfs2_quota_data *qd)
{
	if (atomic_dec_and_lock(&qd->qd_count, &qd_lru_lock)) {
		/* Add to the reclaim list */
		list_add_tail(&qd->qd_reclaim, &qd_lru_list);
		atomic_inc(&qd_lru_count);
		spin_unlock(&qd_lru_lock);
	}
}