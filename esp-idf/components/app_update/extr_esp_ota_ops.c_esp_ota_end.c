#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ handle; scalar_t__ erased_size; scalar_t__ wrote_size; scalar_t__ partial_bytes; TYPE_4__* part; int /*<<< orphan*/  partial_data; } ;
typedef  TYPE_1__ ota_ops_entry_t ;
struct TYPE_11__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ esp_partition_pos_t ;
typedef  scalar_t__ esp_ota_handle_t ;
typedef  int /*<<< orphan*/  esp_image_metadata_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NOT_FOUND ; 
 scalar_t__ ESP_ERR_OTA_VALIDATE_FAILED ; 
 int /*<<< orphan*/  ESP_IMAGE_VERIFY ; 
 scalar_t__ ESP_OK ; 
 TYPE_1__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 scalar_t__ esp_image_verify (int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_partition_write (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  s_ota_ops_entries_head ; 

esp_err_t esp_ota_end(esp_ota_handle_t handle)
{
    ota_ops_entry_t *it;
    esp_err_t ret = ESP_OK;

    for (it = LIST_FIRST(&s_ota_ops_entries_head); it != NULL; it = LIST_NEXT(it, entries)) {
        if (it->handle == handle) {
            break;
        }
    }

    if (it == NULL) {
        return ESP_ERR_NOT_FOUND;
    }

    /* 'it' holds the ota_ops_entry_t for 'handle' */

    // esp_ota_end() is only valid if some data was written to this handle
    if ((it->erased_size == 0) || (it->wrote_size == 0)) {
        ret = ESP_ERR_INVALID_ARG;
        goto cleanup;
    }

    if (it->partial_bytes > 0) {
        /* Write out last 16 bytes, if necessary */
        ret = esp_partition_write(it->part, it->wrote_size, it->partial_data, 16);
        if (ret != ESP_OK) {
            ret = ESP_ERR_INVALID_STATE;
            goto cleanup;
        }
        it->wrote_size += 16;
        it->partial_bytes = 0;
    }

    esp_image_metadata_t data;
    const esp_partition_pos_t part_pos = {
      .offset = it->part->address,
      .size = it->part->size,
    };

    if (esp_image_verify(ESP_IMAGE_VERIFY, &part_pos, &data) != ESP_OK) {
        ret = ESP_ERR_OTA_VALIDATE_FAILED;
        goto cleanup;
    }

 cleanup:
    LIST_REMOVE(it, entries);
    free(it);
    return ret;
}