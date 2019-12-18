#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  tBT_UUID ;
struct TYPE_8__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  properties; int /*<<< orphan*/  end_handle; int /*<<< orphan*/  start_handle; int /*<<< orphan*/  attribute_handle; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ esp_gattc_db_elem_t ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;
struct TYPE_7__ {int /*<<< orphan*/  uu; } ;
struct TYPE_9__ {TYPE_1__ uuid; int /*<<< orphan*/  properties; int /*<<< orphan*/  end_handle; int /*<<< orphan*/  start_handle; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ btgatt_db_element_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_GetGattDb (int,int,int,TYPE_3__**,int*) ; 
 int /*<<< orphan*/  ESP_GATT_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_GATT_OK ; 
 int /*<<< orphan*/  bta_to_btc_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btc128_to_bta_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_3__*) ; 

esp_gatt_status_t btc_ble_gattc_get_db(uint16_t conn_id, uint16_t start_handle, uint16_t end_handle,
                                       esp_gattc_db_elem_t *db, uint16_t *count)
{
    btgatt_db_element_t *get_db = NULL;
    int num = 0;
    tBT_UUID bta_uuid;
    uint16_t db_size = 0;
    BTA_GATTC_GetGattDb(conn_id, start_handle, end_handle, &get_db, &num);

    if (num == 0) {
        if (get_db) {
            osi_free(get_db);
        }
        *count = 0;
        return ESP_GATT_NOT_FOUND;
    }

    db_size = (*count > num) ? num : (*count);
    for (int i = 0; i < db_size; i++) {
        db[i].type = get_db[i].type;
        db[i].attribute_handle = get_db[i].id;
        db[i].start_handle = get_db[i].start_handle;
        db[i].end_handle = get_db[i].end_handle;
        db[i].properties = get_db[i].properties;
        btc128_to_bta_uuid(&bta_uuid, get_db[i].uuid.uu);
        bta_to_btc_uuid(&db[i].uuid, &bta_uuid);
    }
    *count = db_size;
    //don't forget to free the db buffer after used.
    if (get_db) {
        osi_free(get_db);
    }
    return ESP_GATT_OK;
}