#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ vfs_spiffs_dir_t ;
struct TYPE_5__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ esp_spiffs_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_clearerr (int /*<<< orphan*/ ) ; 
 int SPIFFS_closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  spiffs_res_to_errno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfs_spiffs_closedir(void* ctx, DIR* pdir)
{
    assert(pdir);
    esp_spiffs_t * efs = (esp_spiffs_t *)ctx;
    vfs_spiffs_dir_t * dir = (vfs_spiffs_dir_t *)pdir;
    int res = SPIFFS_closedir(&dir->d);
    free(dir);
    if (res < 0) {
        errno = spiffs_res_to_errno(SPIFFS_errno(efs->fs));
        SPIFFS_clearerr(efs->fs);
        return -1;
    }
    return res;
}