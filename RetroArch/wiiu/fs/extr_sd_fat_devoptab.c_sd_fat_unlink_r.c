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
 int ENOMEM ; 
 int FSRemove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* sd_fat_get_device_data (char const*) ; 
 char* sd_fat_real_path (char const*,TYPE_1__*) ; 

__attribute__((used)) static int sd_fat_unlink_r (struct _reent *r, const char *name)
{
    sd_fat_private_t *dev = sd_fat_get_device_data(name);
    if(!dev) {
        r->_errno = ENODEV;
        return -1;
    }

    OSLockMutex(dev->pMutex);

    char *real_path = sd_fat_real_path(name, dev);
    if(!real_path) {
        r->_errno = ENOMEM;
        OSUnlockMutex(dev->pMutex);
        return -1;
    }

    int result = FSRemove(dev->pClient, dev->pCmd, real_path, -1);

    free(real_path);

    OSUnlockMutex(dev->pMutex);

    if(result < 0) {
        r->_errno = result;
        return -1;
    }

    return 0;
}