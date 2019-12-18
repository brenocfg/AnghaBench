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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  esp_gattc_descr_elem_t ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;
typedef  int /*<<< orphan*/  btgatt_db_element_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_GetAllDescriptor (int,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  ESP_GATT_DB_DESCRIPTOR ; 
 int /*<<< orphan*/  ESP_GATT_OK ; 
 int /*<<< orphan*/  btc_gattc_check_valid_param (int,int) ; 
 int /*<<< orphan*/  btc_gattc_fill_gatt_db_conversion (int,int,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

esp_gatt_status_t btc_ble_gattc_get_all_descr(uint16_t conn_id,
                                              uint16_t char_handle,
                                              esp_gattc_descr_elem_t *result,
                                              uint16_t *count, uint16_t offset)
{
    esp_gatt_status_t status;
    btgatt_db_element_t *db = NULL;
    int descr_num = 0;
    BTA_GATTC_GetAllDescriptor(conn_id, char_handle, &db, &descr_num);

    if ((status = btc_gattc_check_valid_param(descr_num, offset)) != ESP_GATT_OK) {
        if (db) {
            osi_free(db);
        }
        *count = 0;
        return status;
    } else {
        btc_gattc_fill_gatt_db_conversion(*count, (uint16_t)descr_num, ESP_GATT_DB_DESCRIPTOR, offset, (void *)result, db);
    }

    *count = descr_num;
    //don't forget to free the db buffer after used.
    if (db) {
        osi_free(db);
    }
    return ESP_GATT_OK;
}