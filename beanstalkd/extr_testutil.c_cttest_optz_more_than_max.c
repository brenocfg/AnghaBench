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
 int job_data_size_limit ; 
 int /*<<< orphan*/  optparse (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  srv ; 

void
cttest_optz_more_than_max()
{
    char *args[] = {
        "-z1073741825",
        NULL,
    };

    optparse(&srv, args);
    assert(job_data_size_limit == 1073741824);
}