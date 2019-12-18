#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; scalar_t__ offset; } ;
typedef  TYPE_1__ esp_partition_pos_t ;
typedef  int /*<<< orphan*/  esp_image_metadata_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_BOOTLOADER_OFFSET ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_IMAGE_VERIFY ; 
 scalar_t__ ESP_PARTITION_TABLE_OFFSET ; 
 int /*<<< orphan*/  esp_image_verify (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

esp_err_t esp_image_verify_bootloader_data(esp_image_metadata_t *data)
{
    if (data == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    const esp_partition_pos_t bootloader_part = {
        .offset = ESP_BOOTLOADER_OFFSET,
        .size = ESP_PARTITION_TABLE_OFFSET - ESP_BOOTLOADER_OFFSET,
    };
    return esp_image_verify(ESP_IMAGE_VERIFY,
                            &bootloader_part,
                            data);
}