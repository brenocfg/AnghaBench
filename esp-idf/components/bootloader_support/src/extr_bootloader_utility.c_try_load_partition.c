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
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ esp_partition_pos_t ;
typedef  int /*<<< orphan*/  esp_image_metadata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ bootloader_load_image (TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool try_load_partition(const esp_partition_pos_t *partition, esp_image_metadata_t *data)
{
    if (partition->size == 0) {
        ESP_LOGD(TAG, "Can't boot from zero-length partition");
        return false;
    }
#ifdef BOOTLOADER_BUILD
    if (bootloader_load_image(partition, data) == ESP_OK) {
        ESP_LOGI(TAG, "Loaded app from partition at offset 0x%x",
                 partition->offset);
        return true;
    }
#endif

    return false;
}