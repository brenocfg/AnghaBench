#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ esp_partition_pos_t ;
typedef  int /*<<< orphan*/  esp_image_metadata_t ;
struct TYPE_10__ {int app_count; TYPE_1__ test; } ;
typedef  TYPE_2__ bootloader_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 int FACTORY_INDEX ; 
 int /*<<< orphan*/  TAG ; 
 int TEST_APP_INDEX ; 
 int /*<<< orphan*/  TRY_LOG_FORMAT ; 
 int /*<<< orphan*/  bootloader_reset () ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ check_anti_rollback (TYPE_1__*) ; 
 TYPE_1__ index_to_partition (TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  load_image (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_invalid_app_partition (int) ; 
 int /*<<< orphan*/  set_actual_ota_seq (TYPE_2__ const*,int) ; 
 scalar_t__ try_load_partition (TYPE_1__*,int /*<<< orphan*/ *) ; 

void bootloader_utility_load_boot_image(const bootloader_state_t *bs, int start_index)
{
    int index = start_index;
    esp_partition_pos_t part;
    esp_image_metadata_t image_data;

    if (start_index == TEST_APP_INDEX) {
        if (try_load_partition(&bs->test, &image_data)) {
            load_image(&image_data);
        } else {
            ESP_LOGE(TAG, "No bootable test partition in the partition table");
            bootloader_reset();
        }
    }

    /* work backwards from start_index, down to the factory app */
    for (index = start_index; index >= FACTORY_INDEX; index--) {
        part = index_to_partition(bs, index);
        if (part.size == 0) {
            continue;
        }
        ESP_LOGD(TAG, TRY_LOG_FORMAT, index, part.offset, part.size);
        if (check_anti_rollback(&part) && try_load_partition(&part, &image_data)) {
            set_actual_ota_seq(bs, index);
            load_image(&image_data);
        }
        log_invalid_app_partition(index);
    }

    /* failing that work forwards from start_index, try valid OTA slots */
    for (index = start_index + 1; index < bs->app_count; index++) {
        part = index_to_partition(bs, index);
        if (part.size == 0) {
            continue;
        }
        ESP_LOGD(TAG, TRY_LOG_FORMAT, index, part.offset, part.size);
        if (check_anti_rollback(&part) && try_load_partition(&part, &image_data)) {
            set_actual_ota_seq(bs, index);
            load_image(&image_data);
        }
        log_invalid_app_partition(index);
    }

    if (try_load_partition(&bs->test, &image_data)) {
        ESP_LOGW(TAG, "Falling back to test app as only bootable partition");
        load_image(&image_data);
    }

    ESP_LOGE(TAG, "No bootable app partitions in the partition table");
    bzero(&image_data, sizeof(esp_image_metadata_t));
    bootloader_reset();
}