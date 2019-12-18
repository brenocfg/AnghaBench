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
typedef  int u64 ;
struct statvfs {int f_bsize; int f_frsize; int f_blocks; int f_bfree; int f_bavail; int f_files; int f_ffree; int f_fsid; int f_namemax; scalar_t__ f_flag; } ;
struct _reent {int _errno; } ;
struct TYPE_4__ {int /*<<< orphan*/  pMutex; int /*<<< orphan*/  pCmd; int /*<<< orphan*/  pClient; } ;
typedef  TYPE_1__ sd_fat_private_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int FSGetFreeSpaceSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (struct statvfs*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sd_fat_get_device_data (char const*) ; 
 char* sd_fat_real_path (char const*,TYPE_1__*) ; 

__attribute__((used)) static int sd_fat_statvfs_r (struct _reent *r, const char *path, struct statvfs *buf)
{
    sd_fat_private_t *dev = sd_fat_get_device_data(path);
    if(!dev) {
        r->_errno = ENODEV;
        return -1;
    }

    OSLockMutex(dev->pMutex);

    /* Zero out the stat buffer */
    memset(buf, 0, sizeof(struct statvfs));

    char *real_path = sd_fat_real_path(path, dev);
    if(!real_path) {
        r->_errno = ENOMEM;
        OSUnlockMutex(dev->pMutex);
        return -1;
    }

    u64 size;

    int result = FSGetFreeSpaceSize(dev->pClient, dev->pCmd, real_path, &size, -1);

    free(real_path);

    if(result < 0) {
        r->_errno = result;
        OSUnlockMutex(dev->pMutex);
        return -1;
    }

    /* File system block size */
    buf->f_bsize = 512;

    /* Fundamental file system block size */
    buf->f_frsize = 512;

    /* Total number of blocks on file system in units of f_frsize */
    buf->f_blocks = size >> 9; /* this is unknown */

    /* Free blocks available for all and for non-privileged processes */
    buf->f_bfree = buf->f_bavail = size >> 9;

    /* Number of inodes at this point in time */
    buf->f_files = 0xffffffff;

    /* Free inodes available for all and for non-privileged processes */
    buf->f_ffree = 0xffffffff;

    /* File system id */
    buf->f_fsid = (int)dev;

    /* Bit mask of f_flag values. */
    buf->f_flag = 0;

    /* Maximum length of filenames */
    buf->f_namemax = 255;

    OSUnlockMutex(dev->pMutex);

    return 0;
}