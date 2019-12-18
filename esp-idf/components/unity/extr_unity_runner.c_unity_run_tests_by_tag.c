#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  desc; struct TYPE_4__* next; } ;
typedef  TYPE_1__ test_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_PRINT_EOL () ; 
 int /*<<< orphan*/  UnityPrint (char const*) ; 
 TYPE_1__* s_unity_tests_first ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  unity_run_single_test (TYPE_1__ const*) ; 

void unity_run_tests_by_tag(const char *tag, bool invert)
{
    UnityPrint("Running tests ");
    if (invert) {
        UnityPrint("NOT ");
    }
    UnityPrint("matching '");
    UnityPrint(tag);
    UnityPrint("'...");
    UNITY_PRINT_EOL();

    for (const test_desc_t *test = s_unity_tests_first; test != NULL; test = test->next) {
        if ((strstr(test->desc, tag) != NULL) == !invert) {
            unity_run_single_test(test);
        }
    }
}