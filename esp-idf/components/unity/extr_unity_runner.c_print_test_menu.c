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
struct TYPE_3__ {char* name; char* desc; int test_fn_count; char** test_fn_name; struct TYPE_3__* next; } ;
typedef  TYPE_1__ test_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_FLUSH () ; 
 int /*<<< orphan*/  UNITY_PRINT_EOL () ; 
 int /*<<< orphan*/  UNITY_PRINT_TAB () ; 
 int /*<<< orphan*/  UnityPrint (char*) ; 
 int /*<<< orphan*/  UnityPrintNumber (int) ; 
 TYPE_1__* s_unity_tests_first ; 

__attribute__((used)) static int print_test_menu(void)
{
    int test_counter = 0;
    UNITY_PRINT_EOL();
    UNITY_PRINT_EOL();
    UnityPrint("Here's the test menu, pick your combo:");
    UNITY_PRINT_EOL();
    for (const test_desc_t *test = s_unity_tests_first;
            test != NULL;
            test = test->next, ++test_counter) {

        UnityPrint("(");
        UnityPrintNumber(test_counter + 1);
        UnityPrint(")");
        UNITY_PRINT_TAB();
        UnityPrint("\"");
        UnityPrint(test->name);
        UnityPrint("\" ");
        UnityPrint(test->desc);
        UNITY_PRINT_EOL();

        if (test->test_fn_count > 1) {
            for (int i = 0; i < test->test_fn_count; i++) {
                UNITY_PRINT_TAB();
                UnityPrint("(");
                UnityPrintNumber(i + 1);
                UnityPrint(")");
                UNITY_PRINT_TAB();
                UnityPrint("\"");
                UnityPrint(test->test_fn_name[i]);
                UnityPrint("\"");
                UNITY_PRINT_EOL();
            }
        }
    }
    UNITY_PRINT_EOL();
    UnityPrint("Enter test for running."); /* unit_test.py needs it for finding the end of test menu */
    UNITY_PRINT_EOL();
    UNITY_OUTPUT_FLUSH();
    return test_counter;
}