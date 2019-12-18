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
struct TYPE_3__ {long offset; int /*<<< orphan*/  path; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ vfs_spiffs_dir_t ;
struct spiffs_dirent {char* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ esp_spiffs_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_opendir (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SPIFFS_readdir (int /*<<< orphan*/ *,struct spiffs_dirent*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  spiffs_res_to_errno (int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static void vfs_spiffs_seekdir(void* ctx, DIR* pdir, long offset)
{
    assert(pdir);
    esp_spiffs_t * efs = (esp_spiffs_t *)ctx;
    vfs_spiffs_dir_t * dir = (vfs_spiffs_dir_t *)pdir;
    struct spiffs_dirent tmp;
    if (offset < dir->offset) {
        //rewind dir
        SPIFFS_closedir(&dir->d);
        if (!SPIFFS_opendir(efs->fs, NULL, &dir->d)) {
            errno = spiffs_res_to_errno(SPIFFS_errno(efs->fs));
            SPIFFS_clearerr(efs->fs);
            return;
        }
        dir->offset = 0;
    }
    while (dir->offset < offset) {
        if (SPIFFS_readdir(&dir->d, &tmp) == 0) {
            errno = spiffs_res_to_errno(SPIFFS_errno(efs->fs));
            SPIFFS_clearerr(efs->fs);
            return;
        }
        size_t plen = strlen(dir->path);
        if (plen > 1) {
            if (strncasecmp(dir->path, (const char *)tmp.name, plen) || tmp.name[plen] != '/' || !tmp.name[plen+1]) {
                continue;
            }
        }
        dir->offset++;
    }
}