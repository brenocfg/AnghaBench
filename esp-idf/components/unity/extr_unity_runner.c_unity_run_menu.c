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
typedef  int /*<<< orphan*/  cmdline ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_BEGIN () ; 
 int /*<<< orphan*/  UNITY_END () ; 
 int /*<<< orphan*/  UNITY_OUTPUT_FLUSH () ; 
 int /*<<< orphan*/  UNITY_PRINT_EOL () ; 
 int /*<<< orphan*/  UnityPrint (char*) ; 
 int get_test_count () ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  print_test_menu () ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  trim_trailing_space (char*) ; 
 int /*<<< orphan*/  unity_gets (char*,int) ; 
 int /*<<< orphan*/  unity_run_all_tests () ; 
 int /*<<< orphan*/  unity_run_single_test_by_index_parse (char*,int) ; 
 int /*<<< orphan*/  unity_run_test_by_name (char*) ; 
 int /*<<< orphan*/  unity_run_tests_by_tag (char*,int) ; 

void unity_run_menu(void)
{
    UNITY_PRINT_EOL();
    UNITY_PRINT_EOL();
    UnityPrint("Press ENTER to see the list of tests.");
    UNITY_PRINT_EOL();
    int test_count = get_test_count();
    while (true) {
        char cmdline[256] = { 0 };
        while (strlen(cmdline) == 0) {
            unity_gets(cmdline, sizeof(cmdline));
            trim_trailing_space(cmdline);
            if (strlen(cmdline) == 0) {
                /* if input was newline, print a new menu */
                print_test_menu();
            }
        }
        /*use '-' to show test history. Need to do it before UNITY_BEGIN cleanup history */
        if (cmdline[0] == '-') {
            UNITY_END();
            continue;
        }

        UNITY_BEGIN();

        size_t idx = 0;
        bool invert = false;
        if (cmdline[idx] == '!') {
            invert = true;
            ++idx;
        }

        if (cmdline[idx] == '*') {
            unity_run_all_tests();
        } else if (cmdline[idx] == '[') {
            unity_run_tests_by_tag(cmdline + idx, invert);
        } else if (cmdline[idx] == '"') {
            char* end = strrchr(cmdline, '"');
            if (end > &cmdline[idx]) {
                *end = 0;
                unity_run_test_by_name(cmdline + idx + 1);
            }
        } else if (isdigit((unsigned char)cmdline[idx])) {
            unity_run_single_test_by_index_parse(cmdline + idx, test_count);
        }

        UNITY_END();

        UnityPrint("Enter next test, or 'enter' to see menu");
        UNITY_PRINT_EOL();
        UNITY_OUTPUT_FLUSH();
    }
}