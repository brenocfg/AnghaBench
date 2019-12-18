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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

bool
atf_utils_file_exists(const char *path)
{
    const int ret = access(path, F_OK);
    if (ret == -1) {
        if (errno != ENOENT)
            atf_tc_fail("Failed to check the existence of %s: %s", path,
                        strerror(errno));
        else
            return false;
    } else
        return true;
}