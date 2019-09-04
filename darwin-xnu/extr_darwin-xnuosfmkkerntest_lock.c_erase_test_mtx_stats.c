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
typedef  size_t uint ;
struct lck_mtx_test_stats_elem {int /*<<< orphan*/  lock; int /*<<< orphan*/  min; scalar_t__ max; scalar_t__ avg; scalar_t__ tot; scalar_t__ samples; } ;

/* Variables and functions */
 size_t TEST_MTX_MAX_STATS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct lck_mtx_test_stats_elem* lck_mtx_test_stats ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
erase_test_mtx_stats(
	uint type)
{
	assert(type < TEST_MTX_MAX_STATS);
	struct lck_mtx_test_stats_elem* stat = &lck_mtx_test_stats[type];

	lck_spin_lock(&stat->lock);

	stat->samples = 0;
	stat->tot = 0;
	stat->avg = 0;
	stat->max = 0;
	stat->min = ~0;

	lck_spin_unlock(&stat->lock);
}