#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ collision_test_vfs_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int collision_test_vfs_open(void* ctx, const char * path, int flags, int mode)
{
    const collision_test_vfs_param_t *param = (collision_test_vfs_param_t *) ctx;
    if (strcmp(param->path, path) == 0) {
        return param->fd;
    }
    errno = ENOENT;
    return -1;
}