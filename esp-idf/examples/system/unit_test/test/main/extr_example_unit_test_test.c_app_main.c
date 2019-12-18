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

/* Variables and functions */
 int /*<<< orphan*/  UNITY_BEGIN () ; 
 int /*<<< orphan*/  UNITY_END () ; 
 int /*<<< orphan*/  print_banner (char*) ; 
 int /*<<< orphan*/  unity_run_all_tests () ; 
 int /*<<< orphan*/  unity_run_menu () ; 
 int /*<<< orphan*/  unity_run_test_by_name (char*) ; 
 int /*<<< orphan*/  unity_run_tests_by_tag (char*,int) ; 

void app_main(void)
{
    /* These are the different ways of running registered tests.
     * In practice, only one of them is usually needed.
     *
     * UNITY_BEGIN() and UNITY_END() calls tell Unity to print a summary
     * (number of tests executed/failed/ignored) of tests executed between these calls.
     */
    print_banner("Executing one test by its name");
    UNITY_BEGIN();
    unity_run_test_by_name("Mean of an empty array is zero");
    UNITY_END();

    print_banner("Running tests with [mean] tag");
    UNITY_BEGIN();
    unity_run_tests_by_tag("[mean]", false);
    UNITY_END();

    print_banner("Running tests without [fails] tag");
    UNITY_BEGIN();
    unity_run_tests_by_tag("[fails]", true);
    UNITY_END();

    print_banner("Running all the registered tests");
    UNITY_BEGIN();
    unity_run_all_tests();
    UNITY_END();

    print_banner("Starting interactive test menu");
    /* This function will not return, and will be busy waiting for UART input.
     * Make sure that task watchdog is disabled if you use this function.
     */
    unity_run_menu();
}