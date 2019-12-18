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
typedef  int /*<<< orphan*/  tBT_UUID ;
typedef  int /*<<< orphan*/  esp_gattc_service_elem_t ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;
typedef  int /*<<< orphan*/  esp_bt_uuid_t ;
typedef  int /*<<< orphan*/  btgatt_db_element_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_GetServiceWithUUID (int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  ESP_GATT_DB_PRIMARY_SERVICE ; 
 int /*<<< orphan*/  ESP_GATT_OK ; 
 int /*<<< orphan*/  btc_gattc_check_valid_param (int,int) ; 
 int /*<<< orphan*/  btc_gattc_fill_gatt_db_conversion (int,int,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btc_to_bta_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * osi_malloc (int) ; 

esp_gatt_status_t btc_ble_gattc_get_service(uint16_t conn_id, esp_bt_uuid_t *svc_uuid,
                                                           esp_gattc_service_elem_t *result,
                                                           uint16_t *count, uint16_t offset)
{
    esp_gatt_status_t status;
    btgatt_db_element_t *db = NULL;
    int svc_num = 0;
    tBT_UUID *bta_uuid = NULL;
    if (svc_uuid) {
        bta_uuid = osi_malloc(sizeof(tBT_UUID));
        btc_to_bta_uuid(bta_uuid, svc_uuid);
    }

    BTA_GATTC_GetServiceWithUUID(conn_id, bta_uuid, &db, &svc_num);

    if ((status = btc_gattc_check_valid_param(svc_num, offset)) != ESP_GATT_OK) {
        if (db) {
            osi_free(db);
        }
        if (bta_uuid) {
            osi_free(bta_uuid);
        }
        *count = 0;
        return status;
    } else {
        btc_gattc_fill_gatt_db_conversion(*count, (uint16_t)svc_num, ESP_GATT_DB_PRIMARY_SERVICE, offset, (void *)result, db);
    }

    *count = svc_num;
    //don't forget to free the db buffer after used.
    if (db) {
        osi_free(db);
    }
    if (bta_uuid) {
        osi_free(bta_uuid);
    }
    return ESP_GATT_OK;
}