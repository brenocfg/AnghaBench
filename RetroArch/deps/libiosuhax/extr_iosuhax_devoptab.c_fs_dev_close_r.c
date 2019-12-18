#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _reent {int _errno; } ;
struct TYPE_4__ {TYPE_1__* dev; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ fs_dev_file_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  pMutex; int /*<<< orphan*/  fsaFd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int IOSUHAX_FSA_CloseFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fs_dev_close_r (struct _reent *r, void *fd)
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

    OSLockMutex(file->dev->pMutex);

    int result = IOSUHAX_FSA_CloseFile(file->dev->fsaFd, file->fd);

    OSUnlockMutex(file->dev->pMutex);

    if(result < 0)
    {
        r->_errno = result;
        return -1;
    }
    return 0;
}