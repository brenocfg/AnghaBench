#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ esp_partition_t ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ esp_partition_pos_t ;
typedef  int /*<<< orphan*/  esp_image_metadata_t ;
typedef  int /*<<< orphan*/  esp_image_load_mode_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_OTA_VALIDATE_FAILED ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ esp_image_verify (int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t image_validate(const esp_partition_t *partition, esp_image_load_mode_t load_mode)
{
    esp_image_metadata_t data;
    const esp_partition_pos_t part_pos = {
        .offset = partition->address,
        .size = partition->size,
    };

    if (esp_image_verify(load_mode, &part_pos, &data) != ESP_OK) {
        return ESP_ERR_OTA_VALIDATE_FAILED;
    }

    return ESP_OK;
}