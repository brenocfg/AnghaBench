#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_pm_lock_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_pm_lock ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  s_list ; 
 int /*<<< orphan*/  s_list_lock ; 

esp_err_t esp_pm_lock_delete(esp_pm_lock_handle_t handle)
{
#ifndef CONFIG_PM_ENABLE
    return ESP_ERR_NOT_SUPPORTED;
#endif

    if (handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (handle->count > 0) {
        return ESP_ERR_INVALID_STATE;
    }
    _lock_acquire(&s_list_lock);
    SLIST_REMOVE(&s_list, handle, esp_pm_lock, next);
    _lock_release(&s_list_lock);
    free(handle);
    return ESP_OK;
}