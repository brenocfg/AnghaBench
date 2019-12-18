#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_nlink; int st_size; int st_blocks; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_mode; } ;
struct _reent {int _errno; } ;
struct TYPE_11__ {TYPE_2__* dev; int /*<<< orphan*/  dirHandle; } ;
typedef  TYPE_3__ sd_fat_dir_entry_t ;
struct TYPE_13__ {scalar_t__ dirStruct; } ;
struct TYPE_9__ {int flag; int size; int /*<<< orphan*/  mtime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  ent_id; int /*<<< orphan*/  group_id; int /*<<< orphan*/  owner_id; } ;
struct TYPE_12__ {TYPE_1__ stat; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  pMutex; int /*<<< orphan*/  pCmd; int /*<<< orphan*/  pClient; } ;
typedef  int /*<<< orphan*/  FSDirectoryEntry ;
typedef  TYPE_4__ FSDirEntry ;
typedef  TYPE_5__ DIR_ITER ;

/* Variables and functions */
 int ENODEV ; 
 int FSReadDir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSLockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSUnlockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_fat_dirnext_r (struct _reent *r, DIR_ITER *dirState, char *filename, struct stat *st)
{
    sd_fat_dir_entry_t *dirIter = (sd_fat_dir_entry_t *)dirState->dirStruct;
    if(!dirIter->dev) {
        r->_errno = ENODEV;
        return -1;
    }

    OSLockMutex(dirIter->dev->pMutex);

    FSDirEntry * dir_entry = malloc(sizeof(FSDirEntry));

    int result = FSReadDir(dirIter->dev->pClient, dirIter->dev->pCmd, dirIter->dirHandle, (FSDirectoryEntry*)dir_entry, -1);
    if(result < 0)
    {
        free(dir_entry);
        r->_errno = result;
        OSUnlockMutex(dirIter->dev->pMutex);
        return -1;
    }

    /* Fetch the current entry */
    strcpy(filename, dir_entry->name);

    if(st)
    {
        memset(st, 0, sizeof(struct stat));
        st->st_mode = (dir_entry->stat.flag & 0x80000000) ? S_IFDIR : S_IFREG;
        st->st_nlink = 1;
        st->st_size = dir_entry->stat.size;
        st->st_blocks = (dir_entry->stat.size + 511) >> 9;
        st->st_dev = dir_entry->stat.ent_id;
        st->st_uid = dir_entry->stat.owner_id;
        st->st_gid = dir_entry->stat.group_id;
        st->st_ino = dir_entry->stat.ent_id;
        st->st_atime = dir_entry->stat.mtime;
        st->st_ctime = dir_entry->stat.ctime;
        st->st_mtime = dir_entry->stat.mtime;
    }

    free(dir_entry);
    OSUnlockMutex(dirIter->dev->pMutex);
    return 0;
}