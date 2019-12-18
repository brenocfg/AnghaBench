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
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ rmdir (char const*) ; 

apr_status_t apr_dir_remove(const char *path, apr_pool_t *pool)
{
    if (rmdir(path) == 0) {
        return APR_SUCCESS;
    }
    else {
        return errno;
    }
}