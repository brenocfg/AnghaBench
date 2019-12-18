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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_test () ; 
 int /*<<< orphan*/  intern_test () ; 
 int /*<<< orphan*/  map_test () ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strf (char*,...) ; 

void common_test(void) {
    buf_test();
    intern_test();
    map_test();

    char *str1 = strf("%d %d", 1, 2);
    assert(strcmp(str1, "1 2") == 0);
    char *str2 = strf("%s %s", str1, str1);
    assert(strcmp(str2, "1 2 1 2") == 0);
    char *str3 = strf("%s asdf %s", str2, str2);
    assert(strcmp(str3, "1 2 1 2 asdf 1 2 1 2") == 0);
}