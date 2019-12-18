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
 char* str_intern (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void intern_test(void) {
    char a[] = "hello";
    assert(strcmp(a, str_intern(a)) == 0);
    assert(str_intern(a) == str_intern(a));
    assert(str_intern(str_intern(a)) == str_intern(a));
    char b[] = "hello";
    assert(a != b);
    assert(str_intern(a) == str_intern(b));
    char c[] = "hello!";
    assert(str_intern(a) != str_intern(c));
    char d[] = "hell";
    assert(str_intern(a) != str_intern(d));
}