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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  esp_gattc_db_elem_t ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;
typedef  int /*<<< orphan*/  esp_gatt_if_t ;

/* Variables and functions */
 scalar_t__ BTC_GATT_CREATE_CONN_ID (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_BLUEDROID_STATUS_ENABLED ; 
 int /*<<< orphan*/  ESP_GATT_INVALID_HANDLE ; 
 int /*<<< orphan*/  ESP_GATT_INVALID_PDU ; 
 int /*<<< orphan*/  btc_ble_gattc_get_db (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

esp_gatt_status_t esp_ble_gattc_get_db(esp_gatt_if_t gattc_if, uint16_t conn_id, uint16_t start_handle, uint16_t end_handle,
                                       esp_gattc_db_elem_t *db, uint16_t *count)
{
    ESP_BLUEDROID_STATUS_CHECK(ESP_BLUEDROID_STATUS_ENABLED);

    if (start_handle == 0 && end_handle == 0) {
        *count = 0;
        return ESP_GATT_INVALID_HANDLE;
    }

    if (db == NULL || count == NULL || *count == 0) {
        return ESP_GATT_INVALID_PDU;
    }

    uint16_t conn_hdl = BTC_GATT_CREATE_CONN_ID(gattc_if, conn_id);
    return btc_ble_gattc_get_db(conn_hdl, start_handle, end_handle, db, count);
}