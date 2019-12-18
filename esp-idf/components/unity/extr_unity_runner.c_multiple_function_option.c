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
struct TYPE_4__ {int test_fn_count; int /*<<< orphan*/  line; int /*<<< orphan*/  name; int /*<<< orphan*/ * fn; } ;
typedef  TYPE_1__ test_desc_t ;
typedef  int /*<<< orphan*/  cmdline ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_PRINT_EOL () ; 
 int /*<<< orphan*/  UnityPrint (char*) ; 
 int /*<<< orphan*/  UnityPrintNumber (int) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  print_multiple_function_test_menu (TYPE_1__ const*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  unity_default_test_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unity_gets (char*,int) ; 

__attribute__((used)) static int multiple_function_option(const test_desc_t *test_ms)
{
    int selection;
    char cmdline[256] = {0};

    print_multiple_function_test_menu(test_ms);
    while (strlen(cmdline) == 0) {
        unity_gets(cmdline, sizeof(cmdline));
        if (strlen(cmdline) == 0) {
            /* if input was newline, print a new menu */
            print_multiple_function_test_menu(test_ms);
        }
    }
    selection = atoi((const char *) cmdline) - 1;
    if (selection >= 0 && selection < test_ms->test_fn_count) {
        unity_default_test_run(test_ms->fn[selection], test_ms->name, test_ms->line);
    } else {
        UnityPrint("Invalid selection, your should input number 1-");
        UnityPrintNumber(test_ms->test_fn_count);
        UNITY_PRINT_EOL();
    }
    return selection;
}