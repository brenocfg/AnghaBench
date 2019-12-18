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
 int /*<<< orphan*/  assertf (int,char*,char*) ; 
 char* fmtalloc (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
cttest_allocf()
{
    char *got;

    got = fmtalloc("hello, %s %d", "world", 5);
    assertf(strcmp("hello, world 5", got) == 0, "got \"%s\"", got);
    free(got);
}