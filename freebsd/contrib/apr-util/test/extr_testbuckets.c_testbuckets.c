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
 int /*<<< orphan*/  test_bwrite ; 
 int /*<<< orphan*/  test_create ; 
 int /*<<< orphan*/  test_flatten ; 
 int /*<<< orphan*/  test_insertfile ; 
 int /*<<< orphan*/  test_manyfile ; 
 int /*<<< orphan*/  test_partition ; 
 int /*<<< orphan*/  test_simple ; 
 int /*<<< orphan*/  test_split ; 
 int /*<<< orphan*/  test_splitline ; 
 int /*<<< orphan*/  test_splits ; 
 int /*<<< orphan*/  test_truncfile ; 
 int /*<<< orphan*/  test_write_putstrs ; 
 int /*<<< orphan*/  test_write_split ; 

abts_suite *testbuckets(abts_suite *suite)
{
    suite = ADD_SUITE(suite);

    abts_run_test(suite, test_create, NULL);
    abts_run_test(suite, test_simple, NULL);
    abts_run_test(suite, test_flatten, NULL);
    abts_run_test(suite, test_split, NULL);
    abts_run_test(suite, test_bwrite, NULL);
    abts_run_test(suite, test_splitline, NULL);
    abts_run_test(suite, test_splits, NULL);
    abts_run_test(suite, test_insertfile, NULL);
    abts_run_test(suite, test_manyfile, NULL);
    abts_run_test(suite, test_truncfile, NULL);
    abts_run_test(suite, test_partition, NULL);
    abts_run_test(suite, test_write_split, NULL);
    abts_run_test(suite, test_write_putstrs, NULL);

    return suite;
}