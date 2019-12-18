#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ offset; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ esp_partition_pos_t ;
typedef  int /*<<< orphan*/  esp_image_segment_header_t ;
typedef  int /*<<< orphan*/  esp_image_header_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {scalar_t__ magic_word; } ;
typedef  TYPE_2__ esp_app_desc_t ;

/* Variables and functions */
 scalar_t__ ESP_APP_DESC_MAGIC_WORD ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * bootloader_mmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootloader_munmap (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 

esp_err_t bootloader_common_get_partition_description(const esp_partition_pos_t *partition, esp_app_desc_t *app_desc)
{
    if (partition == NULL || app_desc == NULL || partition->offset == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    const uint8_t *image = bootloader_mmap(partition->offset, partition->size);
    if (image == NULL) {
        ESP_LOGE(TAG, "bootloader_mmap(0x%x, 0x%x) failed", partition->offset, partition->size);
        return ESP_FAIL;
    }

    memcpy(app_desc, image + sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t), sizeof(esp_app_desc_t));
    bootloader_munmap(image);

    if (app_desc->magic_word != ESP_APP_DESC_MAGIC_WORD) {
        return ESP_ERR_NOT_FOUND;
    }

    return ESP_OK;
}