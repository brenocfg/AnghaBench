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
struct TYPE_2__ {int fd; } ;
typedef  TYPE_1__ collision_test_vfs_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int collision_test_vfs_close(void* ctx, int fd)
{
    const collision_test_vfs_param_t *param = (collision_test_vfs_param_t *) ctx;
    if (fd == param->fd) {
        return 0;
    }
    errno = EBADF;
    return -1;
}