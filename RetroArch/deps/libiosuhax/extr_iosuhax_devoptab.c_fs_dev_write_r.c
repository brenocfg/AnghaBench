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
typedef  size_t ssize_t ;
struct TYPE_4__ {int pos; TYPE_1__* dev; int /*<<< orphan*/  fd; int /*<<< orphan*/  write; } ;
typedef  TYPE_2__ fs_dev_file_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  pMutex; int /*<<< orphan*/  fsaFd; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENODEV ; 
 int IOSUHAX_FSA_WriteFile (int /*<<< orphan*/ ,char const*,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fs_dev_write_r (struct _reent *r, void *fd, const char *ptr, size_t len)
{
    fs_dev_file_state_t *file = (fs_dev_file_state_t *)fd;

    if(!r)
        return 0;

    if(!file) {
        r->_errno = EINVAL;
        return 0;
    }

    if(!file->dev) {
        r->_errno = ENODEV;
        return 0;
    }

    if(!file->write)
    {
        r->_errno = EACCES;
        return 0;
    }

    OSLockMutex(file->dev->pMutex);

    size_t done = 0;

    while(done < len)
    {
        size_t write_size = len - done;

        int result = IOSUHAX_FSA_WriteFile(file->dev->fsaFd, ptr + done, 0x01, write_size, file->fd, 0);
        if(result < 0)
        {
            r->_errno = result;
            break;
        }
        else if(result == 0)
        {
            if(write_size > 0)
                done = 0;
            break;
        }
        else
        {
            done += result;
            file->pos += result;
        }
    }

    OSUnlockMutex(file->dev->pMutex);
    return done;
}