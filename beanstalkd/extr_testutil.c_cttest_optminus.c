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
 int /*<<< orphan*/  assertf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optparse (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  srv ; 
 int /*<<< orphan*/  success ; 

void
cttest_optminus()
{
    char *args[] = {
        "-",
        NULL,
    };

    atexit(success);
    optparse(&srv, args);
    assertf(0, "optparse failed to call exit");
}