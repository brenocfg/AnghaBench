#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lck_mtx_test_stats_elem {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int TEST_MTX_MAX_STATS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enabled ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* lck_mtx_test_stats ; 
 int /*<<< orphan*/  lck_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_mtx_stats_attr ; 
 int /*<<< orphan*/  test_mtx_stats_grp ; 
 int /*<<< orphan*/  test_mtx_stats_grp_attr ; 

__attribute__((used)) static void
init_test_mtx_stats(void)
{
	int i;

	lck_grp_attr_setdefault(&test_mtx_stats_grp_attr);
	lck_grp_init(&test_mtx_stats_grp, "testlck_stats_mtx", &test_mtx_stats_grp_attr);
	lck_attr_setdefault(&test_mtx_stats_attr);

	atomic_store(&enabled, TRUE);
	for(i = 0; i < TEST_MTX_MAX_STATS; i++){
		memset(&lck_mtx_test_stats[i], 0 , sizeof(struct lck_mtx_test_stats_elem));
		lck_mtx_test_stats[i].min = ~0;
		lck_spin_init(&lck_mtx_test_stats[i].lock, &test_mtx_stats_grp, &test_mtx_stats_attr);
	}
}