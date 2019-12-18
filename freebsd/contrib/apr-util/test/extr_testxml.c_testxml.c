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
 int /*<<< orphan*/  test_CVE_2009_3720_alpha ; 
 int /*<<< orphan*/  test_CVE_2009_3720_beta ; 
 int /*<<< orphan*/  test_billion_laughs ; 
 int /*<<< orphan*/  test_xml_parser ; 

abts_suite *testxml(abts_suite *suite)
{
    suite = ADD_SUITE(suite);

    abts_run_test(suite, test_xml_parser, NULL);
    abts_run_test(suite, test_billion_laughs, NULL);
    abts_run_test(suite, test_CVE_2009_3720_alpha, NULL);
    abts_run_test(suite, test_CVE_2009_3720_beta, NULL);

    return suite;
}