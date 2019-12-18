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
struct TYPE_4__ {size_t path_prefix_len; size_t offset; void* ctx; int /*<<< orphan*/  vfs; int /*<<< orphan*/  path_prefix; } ;
typedef  TYPE_1__ vfs_entry_t ;
typedef  int /*<<< orphan*/  esp_vfs_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 size_t ESP_VFS_PATH_MAX ; 
 size_t LEN_PATH_PREFIX_IGNORED ; 
 size_t VFS_MAX_COUNT ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 TYPE_1__** s_vfs ; 
 size_t s_vfs_count ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static esp_err_t esp_vfs_register_common(const char* base_path, size_t len, const esp_vfs_t* vfs, void* ctx, int *vfs_index)
{
    if (len != LEN_PATH_PREFIX_IGNORED) {
        if ((len != 0 && len < 2) || (len > ESP_VFS_PATH_MAX)) {
            return ESP_ERR_INVALID_ARG;
        }
        if ((len > 0 && base_path[0] != '/') || base_path[len - 1] == '/') {
            return ESP_ERR_INVALID_ARG;
        }
    }
    vfs_entry_t *entry = (vfs_entry_t*) malloc(sizeof(vfs_entry_t));
    if (entry == NULL) {
        return ESP_ERR_NO_MEM;
    }
    size_t index;
    for (index = 0; index < s_vfs_count; ++index) {
        if (s_vfs[index] == NULL) {
            break;
        }
    }
    if (index == s_vfs_count) {
        if (s_vfs_count >= VFS_MAX_COUNT) {
            free(entry);
            return ESP_ERR_NO_MEM;
        }
        ++s_vfs_count;
    }
    s_vfs[index] = entry;
    if (len != LEN_PATH_PREFIX_IGNORED) {
        strcpy(entry->path_prefix, base_path); // we have already verified argument length
    } else {
        bzero(entry->path_prefix, sizeof(entry->path_prefix));
    }
    memcpy(&entry->vfs, vfs, sizeof(esp_vfs_t));
    entry->path_prefix_len = len;
    entry->ctx = ctx;
    entry->offset = index;

    if (vfs_index) {
        *vfs_index = index;
    }

    return ESP_OK;
}