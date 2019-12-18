#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_image_segment_header_t ;
typedef  int /*<<< orphan*/  esp_image_header_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_8__ {scalar_t__ magic_word; } ;
typedef  TYPE_2__ esp_app_desc_t ;

/* Variables and functions */
 scalar_t__ ESP_APP_DESC_MAGIC_WORD ; 
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NOT_FOUND ; 
 scalar_t__ ESP_ERR_NOT_SUPPORTED ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ESP_PARTITION_TYPE_APP ; 
 scalar_t__ esp_partition_read (TYPE_1__ const*,int,TYPE_2__*,int) ; 

esp_err_t esp_ota_get_partition_description(const esp_partition_t *partition, esp_app_desc_t *app_desc)
{
    if (partition == NULL || app_desc == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if(partition->type != ESP_PARTITION_TYPE_APP) {
        return ESP_ERR_NOT_SUPPORTED;
    }

    esp_err_t err = esp_partition_read(partition, sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t), app_desc, sizeof(esp_app_desc_t));
    if (err != ESP_OK) {
        return err;
    }

    if (app_desc->magic_word != ESP_APP_DESC_MAGIC_WORD) {
        return ESP_ERR_NOT_FOUND;
    }

    return ESP_OK;
}