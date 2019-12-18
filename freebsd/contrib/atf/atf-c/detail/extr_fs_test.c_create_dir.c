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
 int /*<<< orphan*/  atf_tc_fail (char*,char const*) ; 
 int mkdir (char const*,int) ; 

__attribute__((used)) static
void
create_dir(const char *p, int mode)
{
    int ret;

    ret = mkdir(p, mode);
    if (ret == -1)
        atf_tc_fail("Could not create helper directory %s", p);
}