#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int test_fn_count; int /*<<< orphan*/  line; int /*<<< orphan*/ * fn; int /*<<< orphan*/  desc; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ test_desc_t ;
struct TYPE_6__ {int /*<<< orphan*/  CurrentDetail1; int /*<<< orphan*/  TestFile; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_END () ; 
 int /*<<< orphan*/  UNITY_OUTPUT_FLUSH () ; 
 int /*<<< orphan*/  UNITY_PRINT_EOL () ; 
 TYPE_4__ Unity ; 
 int /*<<< orphan*/  UnityPrint (char*) ; 
 int /*<<< orphan*/  esp_restart () ; 
 int multiple_function_option (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unity_default_test_run (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unity_run_single_test(const test_desc_t *test)
{
    UnityPrint("Running ");
    UnityPrint(test->name);
    UnityPrint("...");
    UNITY_PRINT_EOL();
    // Unit test runner expects to see test name before the test starts
    UNITY_OUTPUT_FLUSH();

    Unity.TestFile = test->file;
    Unity.CurrentDetail1 = test->desc;
    bool reset_after_test = strstr(Unity.CurrentDetail1, "[leaks") != NULL;
    bool multi_device = strstr(Unity.CurrentDetail1, "[multi_device]") != NULL;
    if (test->test_fn_count == 1) {
        unity_default_test_run(test->fn[0], test->name, test->line);
    } else {
        int selection = multiple_function_option(test);
        if (reset_after_test && multi_device == false) {
            if (selection != (test->test_fn_count - 1)) {
                // to do a reset for all stages except the last stage.
                esp_restart();
            }
        }
    }

    if (reset_after_test) {
        // print a result of test before to do reset for the last stage.
        UNITY_END();
        UnityPrint("Enter next test, or 'enter' to see menu");
        UNITY_PRINT_EOL();
        UNITY_OUTPUT_FLUSH();
        esp_restart();
    }
}