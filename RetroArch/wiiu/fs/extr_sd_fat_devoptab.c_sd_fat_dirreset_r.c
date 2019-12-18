#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _reent {int _errno; } ;
struct TYPE_6__ {TYPE_1__* dev; int /*<<< orphan*/  dirHandle; } ;
typedef  TYPE_2__ sd_fat_dir_entry_t ;
struct TYPE_7__ {scalar_t__ dirStruct; } ;
struct TYPE_5__ {int /*<<< orphan*/  pMutex; int /*<<< orphan*/  pCmd; int /*<<< orphan*/  pClient; } ;
typedef  TYPE_3__ DIR_ITER ;

/* Variables and functions */
 int ENODEV ; 
 int FSRewindDir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_fat_dirreset_r (struct _reent *r, DIR_ITER *dirState)
{
    sd_fat_dir_entry_t *dirIter = (sd_fat_dir_entry_t *)dirState->dirStruct;
    if(!dirIter->dev) {
        r->_errno = ENODEV;
        return -1;
    }

    OSLockMutex(dirIter->dev->pMutex);

    int result = FSRewindDir(dirIter->dev->pClient, dirIter->dev->pCmd, dirIter->dirHandle, -1);

    OSUnlockMutex(dirIter->dev->pMutex);

    if(result < 0)
    {
        r->_errno = result;
        return -1;
    }
    return 0;
}