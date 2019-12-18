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
struct TYPE_3__ {char* name; int test_fn_count; char** test_fn_name; } ;
typedef  TYPE_1__ test_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_PRINT_EOL () ; 
 int /*<<< orphan*/  UNITY_PRINT_TAB () ; 
 int /*<<< orphan*/  UnityPrint (char*) ; 
 int /*<<< orphan*/  UnityPrintNumberUnsigned (int) ; 

__attribute__((used)) static void print_multiple_function_test_menu(const test_desc_t *test_ms)
{
    UnityPrint(test_ms->name);
    UNITY_PRINT_EOL();
    for (int i = 0; i < test_ms->test_fn_count; i++) {
        UNITY_PRINT_TAB();
        UnityPrint("(");
        UnityPrintNumberUnsigned(i + 1);
        UnityPrint(")");
        UNITY_PRINT_TAB();
        UnityPrint("\"");
        UnityPrint(test_ms->test_fn_name[i]);
        UnityPrint("\"");
        UNITY_PRINT_EOL();
    }
}