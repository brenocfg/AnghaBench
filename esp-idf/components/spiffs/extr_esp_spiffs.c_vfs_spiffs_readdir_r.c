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
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  path; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ vfs_spiffs_dir_t ;
struct spiffs_dirent {char* name; int /*<<< orphan*/  type; } ;
struct dirent {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; scalar_t__ d_ino; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ esp_spiffs_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_OBJ_NAME_LEN ; 
 int /*<<< orphan*/  SPIFFS_clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ SPIFFS_readdir (int /*<<< orphan*/ *,struct spiffs_dirent*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int spiffs_res_to_errno (int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int vfs_spiffs_readdir_r(void* ctx, DIR* pdir, struct dirent* entry,
                                struct dirent** out_dirent)
{
    assert(pdir);
    esp_spiffs_t * efs = (esp_spiffs_t *)ctx;
    vfs_spiffs_dir_t * dir = (vfs_spiffs_dir_t *)pdir;
    struct spiffs_dirent out;
    size_t plen;
    char * item_name;
    do {
        if (SPIFFS_readdir(&dir->d, &out) == 0) {
            errno = spiffs_res_to_errno(SPIFFS_errno(efs->fs));
            SPIFFS_clearerr(efs->fs);
            if (!errno) {
                *out_dirent = NULL;
            }
            return errno;
        }
        item_name = (char *)out.name;
        plen = strlen(dir->path);

    } while ((plen > 1) && (strncasecmp(dir->path, (const char*)out.name, plen) || out.name[plen] != '/' || !out.name[plen + 1]));

    if (plen > 1) {
        item_name += plen + 1;
    } else if (item_name[0] == '/') {
        item_name++;
    }
    entry->d_ino = 0;
    entry->d_type = out.type;
    snprintf(entry->d_name, SPIFFS_OBJ_NAME_LEN, "%s", item_name);
    dir->offset++;
    *out_dirent = entry;
    return 0;
}