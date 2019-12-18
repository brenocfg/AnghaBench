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
 scalar_t__ exclude ; 
 int find_test_name (char const*) ; 
 int list_tests ; 
 int /*<<< orphan*/ * testlist ; 

__attribute__((used)) static int should_test_run(const char *testname) {
    int found = 0;
    if (list_tests == 1) {
        return 0;
    }
    if (testlist == NULL) {
        return 1;
    }
    found = find_test_name(testname);
    if ((found && !exclude) || (!found && exclude)) {
        return 1;
    }
    return 0;
}