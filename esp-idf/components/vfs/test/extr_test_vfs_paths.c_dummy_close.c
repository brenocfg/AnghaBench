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
struct TYPE_2__ {int called; } ;
typedef  TYPE_1__ dummy_vfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int dummy_close(void* ctx, int fd)
{
    dummy_vfs_t* dummy = (dummy_vfs_t*) ctx;
    dummy->called = true;
    if (fd == 1) {
        return 0;
    }
    errno = EBADF;
    return -1;
}