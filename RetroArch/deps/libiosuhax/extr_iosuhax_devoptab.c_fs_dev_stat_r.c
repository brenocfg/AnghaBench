#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_nlink; int st_size; int st_blocks; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_mode; } ;
struct _reent {int _errno; } ;
struct TYPE_6__ {char* mount_path; int /*<<< orphan*/  pMutex; int /*<<< orphan*/  fsaFd; } ;
typedef  TYPE_1__ fs_dev_private_t ;
struct TYPE_7__ {int flag; int size; int /*<<< orphan*/  mtime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  id; int /*<<< orphan*/  group_id; int /*<<< orphan*/  owner_id; } ;
typedef  TYPE_2__ fileStat_s ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int IOSUHAX_FSA_GetStat (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* fs_dev_get_device_data (char const*) ; 
 char* fs_dev_real_path (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int fs_dev_stat_r (struct _reent *r, const char *path, struct stat *st)
{
    fs_dev_private_t *dev = fs_dev_get_device_data(path);

    if(!r)
        return -1;

    if(!dev) {
        r->_errno = ENODEV;
        return -1;
    }

    OSLockMutex(dev->pMutex);

    // Zero out the stat buffer
    memset(st, 0, sizeof(struct stat));

    char *real_path = fs_dev_real_path(path, dev);
    if(!real_path) {
        r->_errno = ENOMEM;
        OSUnlockMutex(dev->pMutex);
        return -1;
    }

    fileStat_s stats;

    int result = IOSUHAX_FSA_GetStat(dev->fsaFd, real_path, &stats);

    free(real_path);

    if(result < 0) {
        r->_errno = result;
        OSUnlockMutex(dev->pMutex);
        return -1;
    }

    // mark root also as directory
    st->st_mode = ((stats.flag & 0x80000000) || (strlen(dev->mount_path) + 1 == strlen(real_path)))? S_IFDIR : S_IFREG;
    st->st_nlink = 1;
    st->st_size = stats.size;
    st->st_blocks = (stats.size + 511) >> 9;
    // Fill in the generic entry stats
    st->st_dev = stats.id;
    st->st_uid = stats.owner_id;
    st->st_gid = stats.group_id;
    st->st_ino = stats.id;
    st->st_atime = stats.mtime;
    st->st_ctime = stats.ctime;
    st->st_mtime = stats.mtime;

    OSUnlockMutex(dev->pMutex);

    return 0;
}