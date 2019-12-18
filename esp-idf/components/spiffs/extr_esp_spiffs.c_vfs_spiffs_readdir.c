#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  e; } ;
typedef  TYPE_1__ vfs_spiffs_dir_t ;
struct dirent {int dummy; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int errno ; 
 int vfs_spiffs_readdir_r (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dirent**) ; 

__attribute__((used)) static struct dirent* vfs_spiffs_readdir(void* ctx, DIR* pdir)
{
    assert(pdir);
    vfs_spiffs_dir_t * dir = (vfs_spiffs_dir_t *)pdir;
    struct dirent* out_dirent;
    int err = vfs_spiffs_readdir_r(ctx, pdir, &dir->e, &out_dirent);
    if (err != 0) {
        errno = err;
        return NULL;
    }
    return out_dirent;
}