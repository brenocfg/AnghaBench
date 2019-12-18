#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__ user_data; } ;
typedef  TYPE_1__ spiffs ;
typedef  int s32_t ;
struct TYPE_5__ {int /*<<< orphan*/  partition; } ;
typedef  TYPE_2__ esp_spiffs_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_partition_erase_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32_t spiffs_api_erase(spiffs *fs, uint32_t addr, uint32_t size)
{
    esp_err_t err = esp_partition_erase_range(((esp_spiffs_t *)(fs->user_data))->partition, 
                                        addr, size);
    if (err) {
        ESP_LOGE(TAG, "failed to erase addr %08x, size %08x, err %d", addr, size, err);
        return -1;
    }
    return 0;
}