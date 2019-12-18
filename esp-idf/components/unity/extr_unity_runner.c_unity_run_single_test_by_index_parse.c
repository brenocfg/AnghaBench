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
 int /*<<< orphan*/  UNITY_EXEC_TIME_MS () ; 
 int /*<<< orphan*/  UNITY_EXEC_TIME_START () ; 
 int /*<<< orphan*/  UNITY_EXEC_TIME_STOP () ; 
 int /*<<< orphan*/  UNITY_OUTPUT_FLUSH () ; 
 int /*<<< orphan*/  UNITY_PRINT_EOL () ; 
 int /*<<< orphan*/  UnityPrint (char*) ; 
 int /*<<< orphan*/  UnityPrintNumberUnsigned (int /*<<< orphan*/ ) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unity_run_single_test_by_index (int) ; 

__attribute__((used)) static void unity_run_single_test_by_index_parse(const char *filter, int index_max)
{
    int test_index = strtol(filter, NULL, 10);
    if (test_index >= 1 && test_index <= index_max) {
        UNITY_EXEC_TIME_START();
        unity_run_single_test_by_index(test_index - 1);
        UNITY_EXEC_TIME_STOP();
        UnityPrint("Test ran in ");
        UnityPrintNumberUnsigned(UNITY_EXEC_TIME_MS());
        UnityPrint("ms");
        UNITY_PRINT_EOL();
        UNITY_OUTPUT_FLUSH();
    }
}