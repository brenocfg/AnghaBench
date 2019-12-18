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
struct TYPE_3__ {int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  optparse (TYPE_1__*,char**) ; 
 TYPE_1__ srv ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void
cttest_optu()
{
    char *args[] = {
        "-ukr",
        NULL,
    };

    optparse(&srv, args);
    assert(strcmp(srv.user, "kr") == 0);
}