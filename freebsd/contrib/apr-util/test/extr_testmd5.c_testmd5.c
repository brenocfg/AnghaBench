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
 scalar_t__ count ; 
 scalar_t__ num_sums ; 
 int /*<<< orphan*/  test_md5sum ; 
 int /*<<< orphan*/  test_md5sum_unaligned ; 

abts_suite *testmd5(abts_suite *suite)
{
        suite = ADD_SUITE(suite);
        
        for (count=0; count < num_sums; count++) {
            abts_run_test(suite, test_md5sum, NULL);
        }
        abts_run_test(suite, test_md5sum_unaligned, NULL);

        return suite;
}