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
struct _reent {int /*<<< orphan*/  _errno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ fs_dev_file_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOTSUP ; 

__attribute__((used)) static int fs_dev_fsync_r (struct _reent *r, void *fd)
{
    fs_dev_file_state_t *file = (fs_dev_file_state_t *)fd;

    if(!r)
        return -1;

    if(!file) {
        r->_errno = EINVAL;
        return -1;
    }

    if(!file->dev) {
        r->_errno = ENODEV;
        return -1;
    }

    r->_errno = ENOTSUP;
    /* TODO */
    return -1;
}