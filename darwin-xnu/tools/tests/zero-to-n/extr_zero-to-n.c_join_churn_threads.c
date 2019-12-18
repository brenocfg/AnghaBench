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
typedef  size_t uint32_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errc (int /*<<< orphan*/ ,scalar_t__,char*,size_t) ; 
 size_t g_churn_count ; 
 int /*<<< orphan*/  g_churn_stop ; 
 int /*<<< orphan*/  g_churn_stopped_at ; 
 int /*<<< orphan*/ * g_churn_threads ; 
 int /*<<< orphan*/  memory_order_seq_cst ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
join_churn_threads(void)
{
	if (atomic_load_explicit(&g_churn_stopped_at, memory_order_seq_cst) != 0)
		printf("Warning: Some of the churn threads may have stopped early: %lld\n",
		       g_churn_stopped_at);

	atomic_store_explicit(&g_churn_stop, TRUE, memory_order_seq_cst);

	/* Rejoin churn threads */
	for (uint32_t i = 0; i < g_churn_count; i++) {
		errno_t err = pthread_join(g_churn_threads[i], NULL);
		if (err) errc(EX_OSERR, err, "pthread_join %d", i);
	}
}