#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint16_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_4__ {float max; float min; scalar_t__ opt1; } ;
struct TYPE_5__ {scalar_t__ timestamp; scalar_t__ param_units; int /*<<< orphan*/ * param_key; TYPE_1__ param_opts; int /*<<< orphan*/ * instance_ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ characteristic_descriptor_t ;

/* Variables and functions */
 int CID_RELAY_P1 ; 
 int CID_RELAY_P2 ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK_WITHOUT_ABORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int,char*,char*,int,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ MODBUS_VALUE_UPDATE_TIMEOUT_US ; 
 int /*<<< orphan*/  SENSE_MAIN_TAG ; 
 int /*<<< orphan*/  TIMEOUT_UPDATE_CIDS_TICS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_err_to_name (scalar_t__) ; 
 scalar_t__ esp_timer_get_time () ; 
 int /*<<< orphan*/  sense_modbus_get_cid_data (int,TYPE_2__*) ; 
 scalar_t__ sense_modbus_read_value (int,void*) ; 
 int /*<<< orphan*/  sense_modbus_send_value (int,int*) ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void trigger_operation_task(void *arg)
{
    float value;
    uint64_t timeout = 0;
    uint16_t temp_value = 0;
    bool alarm_state = false;
    bool relay_state = false;
    characteristic_descriptor_t cid_data = { 0 };

    while (1) {
        alarm_state = false;
        for (int cid = 0; cid < (CID_RELAY_P2); cid++)
        {
            // Get cid data
            ESP_ERROR_CHECK_WITHOUT_ABORT(sense_modbus_get_cid_data(cid, &cid_data));
            assert(cid_data.param_key != NULL);
            assert(cid_data.instance_ptr != NULL);
            // If value is not updated during 10 seconds then update it
            timeout = esp_timer_get_time();
            value = *(float*)cid_data.instance_ptr;
            // Check limits to set alarm if exceeded limit
            if (((value > cid_data.param_opts.max) ||
                    (value < cid_data.param_opts.min)) &&
                    (cid != CID_RELAY_P1)) {
                alarm_state = true;
            }
            if (timeout > (cid_data.timestamp + MODBUS_VALUE_UPDATE_TIMEOUT_US)) {
                // The value is not updated during timeout then update it
                // The actual value is saved in the instance storage
                value = 0;
                esp_err_t error = sense_modbus_read_value(cid, (void*)&value);
                if (error != ESP_OK) {
                    ESP_LOGE(SENSE_MAIN_TAG, "Update failed for cid: %u, %s(%s) = %d, %s",
                                                (uint16_t)cid,
                                                (char*)cid_data.param_key,
                                                (char*)cid_data.param_units,
                                                *(int*)cid_data.instance_ptr,
                                                (char*)esp_err_to_name(error));
                } else {
                    // Update state of alarm
                    if (cid == CID_RELAY_P1) {
                        // Get actual relay state
                        relay_state = (*(uint16_t*)(cid_data.instance_ptr)
                                            & (uint16_t)(cid_data.param_opts.opt1));
                        const char* relay_state_str = relay_state ? "ON" : "OFF";
                        ESP_LOGI(SENSE_MAIN_TAG, "cid: %u, (%s) = %s", (uint16_t)cid,
                                                    (char*)cid_data.param_key,
                                                    (const char*)relay_state_str);
                    } else {
                        // Update read value
                        ESP_LOGI(SENSE_MAIN_TAG, "cid: %u, %s(%s) = %.2f", (uint16_t)cid,
                                                (char*)cid_data.param_key,
                                                (char*)cid_data.param_units,
                                                (float)value);
                    }
                }
            }
        }
        // Check all characteristics if they exceed limits and set alarm accordingly
        if (!alarm_state) {
            if (relay_state == true) {
                ESP_LOGI(SENSE_MAIN_TAG, "The values within the limit, then release relay.");
                temp_value = 0;
                // Release the relay in IO slave device
                // Do not check an error in this example (IO slave may be not configured)
                (void)sense_modbus_send_value(CID_RELAY_P1, &temp_value); 
                relay_state = false;
            }
        } else {
            if (!relay_state) {
                ESP_LOGI(SENSE_MAIN_TAG, "The value exceeds limit, then set relay.");
                temp_value = 0x00FF;
                (void)sense_modbus_send_value(CID_RELAY_P1, &temp_value); // Set the relay
                relay_state = true;
            }
        }

        vTaskDelay(TIMEOUT_UPDATE_CIDS_TICS);
    }
    vTaskDelete(NULL);
}