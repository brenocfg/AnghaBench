#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; int st_blocks; int st_nlink; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_mode; } ;
struct _reent {int _errno; } ;
struct TYPE_5__ {TYPE_1__* dev; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ sd_fat_file_state_t ;
struct TYPE_6__ {int size; int /*<<< orphan*/  mtime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  ent_id; int /*<<< orphan*/  group_id; int /*<<< orphan*/  owner_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  pMutex; int /*<<< orphan*/  pCmd; int /*<<< orphan*/  pClient; } ;
typedef  TYPE_3__ FSStat__ ;
typedef  int /*<<< orphan*/  FSStat ;

/* Variables and functions */
 int ENODEV ; 
 int FSGetStatFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_fat_fstat_r (struct _reent *r, void* fd, struct stat *st)
{
    sd_fat_file_state_t *file = (sd_fat_file_state_t *)fd;
    if(!file->dev) {
        r->_errno = ENODEV;
        return -1;
    }

    OSLockMutex(file->dev->pMutex);

    /* Zero out the stat buffer */
    memset(st, 0, sizeof(struct stat));

    FSStat__ stats;
    int result = FSGetStatFile(file->dev->pClient, file->dev->pCmd, file->fd, (FSStat*)&stats, -1);
    if(result != 0) {
        r->_errno = result;
        OSUnlockMutex(file->dev->pMutex);
        return -1;
    }

    st->st_mode = S_IFREG;
    st->st_size = stats.size;
    st->st_blocks = (stats.size + 511) >> 9;
    st->st_nlink = 1;

    /* Fill in the generic entry stats */
    st->st_dev = stats.ent_id;
    st->st_uid = stats.owner_id;
    st->st_gid = stats.group_id;
    st->st_ino = stats.ent_id;
    st->st_atime = stats.mtime;
    st->st_ctime = stats.ctime;
    st->st_mtime = stats.mtime;
    OSUnlockMutex(file->dev->pMutex);
    return 0;
}