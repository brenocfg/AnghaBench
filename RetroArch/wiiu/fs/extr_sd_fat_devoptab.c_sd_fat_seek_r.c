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
struct _reent {int /*<<< orphan*/  _errno; } ;
struct TYPE_4__ {int pos; int len; TYPE_1__* dev; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ sd_fat_file_state_t ;
typedef  int off_t ;
struct TYPE_3__ {int /*<<< orphan*/  pMutex; int /*<<< orphan*/  pCmd; int /*<<< orphan*/  pClient; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int FSSetPosFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 

__attribute__((used)) static off_t sd_fat_seek_r (struct _reent *r, void* fd, off_t pos, int dir)
{
    sd_fat_file_state_t *file = (sd_fat_file_state_t *)fd;
    if(!file->dev) {
        r->_errno = ENODEV;
        return 0;
    }

    OSLockMutex(file->dev->pMutex);

    switch(dir)
    {
    case SEEK_SET:
        file->pos = pos;
        break;
    case SEEK_CUR:
        file->pos += pos;
        break;
    case SEEK_END:
        file->pos = file->len + pos;
        break;
    default:
        r->_errno = EINVAL;
        return -1;
    }

    int result = FSSetPosFile(file->dev->pClient, file->dev->pCmd, file->fd, file->pos, -1);

    OSUnlockMutex(file->dev->pMutex);

    if(result == 0)
    {
        return file->pos;
    }

    return result;
}