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
typedef  scalar_t__ esp_vfs_id_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int vfs_index; int permanent; int local_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,scalar_t__,int,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int MAX_FDS ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_err_to_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* s_fd_table ; 
 int /*<<< orphan*/  s_fd_table_lock ; 
 scalar_t__ s_vfs_count ; 

esp_err_t esp_vfs_register_fd(esp_vfs_id_t vfs_id, int *fd)
{
    if (vfs_id < 0 || vfs_id >= s_vfs_count || fd == NULL) {
        ESP_LOGD(TAG, "Invalid arguments for esp_vfs_register_fd(%d, 0x%x)", vfs_id, (int) fd);
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = ESP_ERR_NO_MEM;
    _lock_acquire(&s_fd_table_lock);
    for (int i = 0; i < MAX_FDS; ++i) {
        if (s_fd_table[i].vfs_index == -1) {
            s_fd_table[i].permanent = true;
            s_fd_table[i].vfs_index = vfs_id;
            s_fd_table[i].local_fd = i;
            *fd = i;
            ret = ESP_OK;
            break;
        }
    }
    _lock_release(&s_fd_table_lock);

    ESP_LOGD(TAG, "esp_vfs_register_fd(%d, 0x%x) finished with %s", vfs_id, (int) fd, esp_err_to_name(ret));

    return ret;
}