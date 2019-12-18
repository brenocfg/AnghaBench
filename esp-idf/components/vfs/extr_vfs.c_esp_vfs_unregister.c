#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t const path_prefix_len; int /*<<< orphan*/  path_prefix; } ;
typedef  TYPE_1__ vfs_entry_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {size_t vfs_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__ FD_TABLE_ENTRY_UNUSED ; 
 int MAX_FDS ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t const) ; 
 TYPE_3__* s_fd_table ; 
 int /*<<< orphan*/  s_fd_table_lock ; 
 TYPE_1__** s_vfs ; 
 size_t s_vfs_count ; 
 size_t strlen (char const*) ; 

esp_err_t esp_vfs_unregister(const char* base_path)
{
    const size_t base_path_len = strlen(base_path);
    for (size_t i = 0; i < s_vfs_count; ++i) {
        vfs_entry_t* vfs = s_vfs[i];
        if (vfs == NULL) {
            continue;
        }
        if (base_path_len == vfs->path_prefix_len &&
                memcmp(base_path, vfs->path_prefix, vfs->path_prefix_len) == 0) {
            free(vfs);
            s_vfs[i] = NULL;

            _lock_acquire(&s_fd_table_lock);
            // Delete all references from the FD lookup-table
            for (int j = 0; j < MAX_FDS; ++j) {
                if (s_fd_table[j].vfs_index == i) {
                    s_fd_table[j] = FD_TABLE_ENTRY_UNUSED;
                }
            }
            _lock_release(&s_fd_table_lock);

            return ESP_OK;
        }
    }
    return ESP_ERR_INVALID_STATE;
}