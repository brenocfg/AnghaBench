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
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ ** testlist ; 

__attribute__((used)) static int find_test_name(const char *testname) {
    int i;
    for (i = 0; testlist[i] != NULL; i++) {
        if (!strcmp(testlist[i], testname)) {
            return 1;
        }
    }
    return 0;
}