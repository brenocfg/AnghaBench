#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vfs_fat_ctx_t ;
struct TYPE_6__ {int fattrib; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_2__ FILINFO ;

/* Variables and functions */
 int AM_RDO ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ FR_OK ; 
 int W_OK ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ f_stat (char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  prepend_drive_to_path (TYPE_1__*,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfs_fat_access(void* ctx, const char *path, int amode)
{
    FILINFO info;
    int ret = 0;
    FRESULT res;

    vfs_fat_ctx_t* fat_ctx = (vfs_fat_ctx_t*) ctx;

    _lock_acquire(&fat_ctx->lock);
    prepend_drive_to_path(fat_ctx, &path, NULL);
    res = f_stat(path, &info);
    _lock_release(&fat_ctx->lock);

    if (res == FR_OK) {
        if (((amode & W_OK) == W_OK) && ((info.fattrib & AM_RDO) == AM_RDO)) {
            ret = -1;
            errno = EACCES;
        }
        // There is no flag to test readable or executable: we assume that if
        // it exists then it is readable and executable
    } else {
        ret = -1;
        errno = ENOENT;
    }

    return ret;
}