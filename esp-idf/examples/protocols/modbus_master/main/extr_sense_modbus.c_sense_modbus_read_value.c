#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint16_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_3__ {size_t cid; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  instance_size; scalar_t__ status; int /*<<< orphan*/ * param_key; int /*<<< orphan*/ * instance_ptr; } ;
typedef  TYPE_1__ characteristic_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ PARAM_TYPE_ASCII ; 
 int /*<<< orphan*/  SENSE_MB_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__** active_cid_table ; 
 size_t active_cid_table_size ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ mbc_master_get_parameter (size_t,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sense_modbus_get_time_stamp_us () ; 

esp_err_t sense_modbus_read_value(uint16_t cid, void *value)
{
    assert(active_cid_table != NULL);
    SENSE_MB_CHECK((value != NULL), ESP_ERR_INVALID_ARG, "incorrect value pointer.");
    SENSE_MB_CHECK((cid < active_cid_table_size), ESP_ERR_INVALID_ARG, "incorrect cid to read.");
    characteristic_descriptor_t* cid_info = active_cid_table[cid];
    SENSE_MB_CHECK((cid_info->instance_ptr != NULL), ESP_ERR_INVALID_STATE, "incorrect cid table instance_pointer.");
    SENSE_MB_CHECK((cid_info->param_key != NULL), ESP_ERR_INVALID_STATE, "incorrect cid table or not initialized.");
    SENSE_MB_CHECK((cid_info->cid == cid), ESP_ERR_INVALID_STATE, "incorrect cid table or not initialized.");

    // Set the data pointer for get request to value instance
    uint8_t* value_ptr = (uint8_t*)cid_info->instance_ptr;
    uint8_t type = 0;
    memset((void*)value_ptr, 0, cid_info->instance_size); // Clear value instance first

    // Send Modbus request to read cid correspond registers
    esp_err_t error = mbc_master_get_parameter(cid, (char*)cid_info->param_key, value_ptr, &type);
    SENSE_MB_CHECK((type <= PARAM_TYPE_ASCII), ESP_ERR_NOT_SUPPORTED, "returned data type is not supported (%u)", type);
    cid_info->status = error; // Keep last read status of the cid in the information table
    if (error == ESP_OK) {
        // Copy the value to param
        memcpy((void*)value, (void*)value_ptr, cid_info->instance_size);
        cid_info->timestamp = sense_modbus_get_time_stamp_us(); // Set timestamp of last access to cid
    }
    return error;
}