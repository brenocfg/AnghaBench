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
struct TYPE_5__ {int /*<<< orphan*/  path; scalar_t__ offset; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ vfs_spiffs_dir_t ;
struct TYPE_6__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ esp_spiffs_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SPIFFS_OBJ_NAME_LEN ; 
 int /*<<< orphan*/  SPIFFS_clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_opendir (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  spiffs_res_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DIR* vfs_spiffs_opendir(void* ctx, const char* name)
{
    assert(name);
    esp_spiffs_t * efs = (esp_spiffs_t *)ctx;
    vfs_spiffs_dir_t * dir = calloc(1, sizeof(vfs_spiffs_dir_t));
    if (!dir) {
        errno = ENOMEM;
        return NULL;
    }
    if (!SPIFFS_opendir(efs->fs, name, &dir->d)) {
        free(dir);
        errno = spiffs_res_to_errno(SPIFFS_errno(efs->fs));
        SPIFFS_clearerr(efs->fs);
        return NULL;
    }
    dir->offset = 0;
    strlcpy(dir->path, name, SPIFFS_OBJ_NAME_LEN);
    return (DIR*) dir;
}