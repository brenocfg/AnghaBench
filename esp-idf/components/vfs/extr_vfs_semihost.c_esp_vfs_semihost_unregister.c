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
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {scalar_t__* base_path; scalar_t__* host_path; } ;

/* Variables and functions */
 int CONFIG_SEMIHOSTFS_MAX_MOUNT_POINTS ; 
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_vfs_unregister (scalar_t__*) ; 
 TYPE_1__* s_semhost_ctx ; 
 scalar_t__ strcmp (char const*,scalar_t__*) ; 

esp_err_t esp_vfs_semihost_unregister(const char* base_path)
{
    ESP_LOGD(TAG, "Unregister semihosting driver @ '%s'", base_path);
    int i = 0;
    for (i = 0; i < CONFIG_SEMIHOSTFS_MAX_MOUNT_POINTS; i++) {
        if (s_semhost_ctx[i].base_path[0] != 0 && strcmp(base_path, s_semhost_ctx[i].base_path) == 0) {
            break;
        }
    }
    if (i == CONFIG_SEMIHOSTFS_MAX_MOUNT_POINTS) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_err_t ret = esp_vfs_unregister(s_semhost_ctx[i].base_path);
    if (ret != ESP_OK) {
        return ret;
    }
    s_semhost_ctx[i].base_path[0] = 0;
    s_semhost_ctx[i].host_path[0] = 0;
    ESP_LOGD(TAG, "Unregistered semihosting driver @ '%s'", base_path);
    return ESP_OK;
}