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
typedef  int /*<<< orphan*/  abts_suite ;

/* Variables and functions */
 int /*<<< orphan*/ * ADD_SUITE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abts_run_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_queue_producer_consumer ; 

abts_suite *testqueue(abts_suite *suite)
{
    suite = ADD_SUITE(suite);

#if APR_HAS_THREADS
    abts_run_test(suite, test_queue_producer_consumer, NULL);
#endif /* APR_HAS_THREADS */

    return suite;
}