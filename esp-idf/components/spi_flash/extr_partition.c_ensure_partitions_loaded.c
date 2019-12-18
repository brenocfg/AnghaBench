#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 scalar_t__ load_partitions () ; 
 int /*<<< orphan*/  s_partition_list ; 
 int /*<<< orphan*/  s_partition_list_lock ; 

__attribute__((used)) static esp_err_t ensure_partitions_loaded(void)
{
    esp_err_t err = ESP_OK;
    if (SLIST_EMPTY(&s_partition_list)) {
        // only lock if list is empty (and check again after acquiring lock)
        _lock_acquire(&s_partition_list_lock);
        if (SLIST_EMPTY(&s_partition_list)) {
            ESP_LOGD(TAG, "Loading the partition table");
            err = load_partitions();
            if (err != ESP_OK) {
                ESP_LOGE(TAG, "load_partitions returned 0x%x", err);
            }
        }
        _lock_release(&s_partition_list_lock);
    }
    return err;
}