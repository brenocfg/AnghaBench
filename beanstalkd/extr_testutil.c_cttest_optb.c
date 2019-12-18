#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int use; int /*<<< orphan*/  dir; } ;
struct TYPE_5__ {TYPE_1__ wal; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  optparse (TYPE_2__*,char**) ; 
 TYPE_2__ srv ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void
cttest_optb()
{
    char *args[] = {
        "-bfoo",
        NULL,
    };

    optparse(&srv, args);
    assert(strcmp(srv.wal.dir, "foo") == 0);
    assert(srv.wal.use == 1);
}