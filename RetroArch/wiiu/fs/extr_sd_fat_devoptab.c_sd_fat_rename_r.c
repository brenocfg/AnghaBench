#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _reent {int _errno; } ;
struct TYPE_4__ {int /*<<< orphan*/  pMutex; int /*<<< orphan*/  pCmd; int /*<<< orphan*/  pClient; } ;
typedef  TYPE_1__ sd_fat_private_t ;

/* Variables and functions */
 int ENODEV ; 
 void* ENOMEM ; 
 int FSRename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* sd_fat_get_device_data (char const*) ; 
 char* sd_fat_real_path (char const*,TYPE_1__*) ; 

__attribute__((used)) static int sd_fat_rename_r (struct _reent *r, const char *oldName, const char *newName)
{
    sd_fat_private_t *dev = sd_fat_get_device_data(oldName);
    if(!dev) {
        r->_errno = ENODEV;
        return -1;
    }

    OSLockMutex(dev->pMutex);

    char *real_oldpath = sd_fat_real_path(oldName, dev);
    if(!real_oldpath) {
        r->_errno = ENOMEM;
        OSUnlockMutex(dev->pMutex);
        return -1;
    }
    char *real_newpath = sd_fat_real_path(newName, dev);
    if(!real_newpath) {
        r->_errno = ENOMEM;
        free(real_oldpath);
        OSUnlockMutex(dev->pMutex);
        return -1;
    }

    int result = FSRename(dev->pClient, dev->pCmd, real_oldpath, real_newpath, -1);

    free(real_oldpath);
    free(real_newpath);

    OSUnlockMutex(dev->pMutex);

    if(result < 0) {
        r->_errno = result;
        return -1;
    }

    return 0;

}