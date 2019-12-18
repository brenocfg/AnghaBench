#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_6__ {TYPE_1__ uuid; } ;
struct TYPE_8__ {int /*<<< orphan*/  attribute_handle; TYPE_2__ uuid; } ;
struct TYPE_7__ {int /*<<< orphan*/  remote_bda; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATTC_TAG ; 
 size_t PROFILE_APP_ID ; 
 scalar_t__ SPP_IDX_SPP_DATA_NTY_VAL ; 
 scalar_t__ SPP_IDX_SPP_HEARTBEAT_VAL ; 
 scalar_t__ SPP_IDX_SPP_STATUS_VAL ; 
 int /*<<< orphan*/  cmd_reg_queue ; 
 TYPE_4__* db ; 
 int /*<<< orphan*/  esp_ble_gattc_register_for_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* gl_profile_tab ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  spp_gattc_if ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 scalar_t__ xQueueReceive (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

void spp_client_reg_task(void* arg)
{
    uint16_t cmd_id;
    for(;;) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        if(xQueueReceive(cmd_reg_queue, &cmd_id, portMAX_DELAY)) {
            if(db != NULL) {
                if(cmd_id == SPP_IDX_SPP_DATA_NTY_VAL){
                    ESP_LOGI(GATTC_TAG,"Index = %d,UUID = 0x%04x, handle = %d \n", cmd_id, (db+SPP_IDX_SPP_DATA_NTY_VAL)->uuid.uuid.uuid16, (db+SPP_IDX_SPP_DATA_NTY_VAL)->attribute_handle);
                    esp_ble_gattc_register_for_notify(spp_gattc_if, gl_profile_tab[PROFILE_APP_ID].remote_bda, (db+SPP_IDX_SPP_DATA_NTY_VAL)->attribute_handle);
                }else if(cmd_id == SPP_IDX_SPP_STATUS_VAL){
                    ESP_LOGI(GATTC_TAG,"Index = %d,UUID = 0x%04x, handle = %d \n", cmd_id, (db+SPP_IDX_SPP_STATUS_VAL)->uuid.uuid.uuid16, (db+SPP_IDX_SPP_STATUS_VAL)->attribute_handle);
                    esp_ble_gattc_register_for_notify(spp_gattc_if, gl_profile_tab[PROFILE_APP_ID].remote_bda, (db+SPP_IDX_SPP_STATUS_VAL)->attribute_handle);
                }
#ifdef SUPPORT_HEARTBEAT
                else if(cmd_id == SPP_IDX_SPP_HEARTBEAT_VAL){
                    ESP_LOGI(GATTC_TAG,"Index = %d,UUID = 0x%04x, handle = %d \n", cmd_id, (db+SPP_IDX_SPP_HEARTBEAT_VAL)->uuid.uuid.uuid16, (db+SPP_IDX_SPP_HEARTBEAT_VAL)->attribute_handle);
                    esp_ble_gattc_register_for_notify(spp_gattc_if, gl_profile_tab[PROFILE_APP_ID].remote_bda, (db+SPP_IDX_SPP_HEARTBEAT_VAL)->attribute_handle);
                }
#endif
            }
        }
    }
}