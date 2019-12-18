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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ tBT_UUID ;
typedef  int /*<<< orphan*/  esp_gattc_char_elem_t ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;
typedef  int /*<<< orphan*/  esp_bt_uuid_t ;
typedef  int /*<<< orphan*/  btgatt_db_element_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_GetCharByUUID (int,int,int,TYPE_1__,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  ESP_GATT_DB_CHARACTERISTIC ; 
 int /*<<< orphan*/  ESP_GATT_OK ; 
 int /*<<< orphan*/  btc_gattc_check_valid_param (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_gattc_fill_gatt_db_conversion (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btc_to_bta_uuid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

esp_gatt_status_t btc_ble_gattc_get_char_by_uuid(uint16_t conn_id,
                                                 uint16_t start_handle,
                                                 uint16_t end_handle,
                                                 esp_bt_uuid_t char_uuid,
                                                 esp_gattc_char_elem_t *result,
                                                 uint16_t *count)
{
    esp_gatt_status_t status;
    btgatt_db_element_t *db = NULL;
    int char_num = 0;
    tBT_UUID bta_uuid = {0};
    btc_to_bta_uuid(&bta_uuid, &char_uuid);
    BTA_GATTC_GetCharByUUID(conn_id, start_handle, end_handle, bta_uuid, &db, &char_num);

    if ((status = btc_gattc_check_valid_param(char_num, 0)) != ESP_GATT_OK) {
        if (db) {
            osi_free(db);
        }
        *count = 0;
        return status;
    } else {
        btc_gattc_fill_gatt_db_conversion(*count, (uint16_t)char_num, ESP_GATT_DB_CHARACTERISTIC, 0, (void *)result, db);
    }

    *count = char_num;
    //don't forget to free the db buffer after used.
    if (db) {
        osi_free(db);
    }
    return ESP_GATT_OK;
}