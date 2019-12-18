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
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {size_t cid; scalar_t__ instance_type; int change_flag; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  status; int /*<<< orphan*/ * param_key; int /*<<< orphan*/  instance_size; int /*<<< orphan*/ * instance_ptr; } ;
typedef  TYPE_1__ characteristic_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 scalar_t__ PARAM_TYPE_ASCII ; 
 int /*<<< orphan*/  SENSE_MB_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__** active_cid_table ; 
 size_t active_cid_table_size ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbc_master_set_parameter (size_t,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sense_modbus_get_time_stamp_us () ; 

esp_err_t sense_modbus_send_value(uint16_t cid, void* value)
{
    assert(active_cid_table != NULL);
    SENSE_MB_CHECK((cid < active_cid_table_size), ESP_ERR_INVALID_ARG, "incorrect cid to set.");
    characteristic_descriptor_t* cid_info = active_cid_table[cid];
    SENSE_MB_CHECK((cid_info->instance_ptr != NULL), ESP_ERR_INVALID_STATE, "incorrect cid table instance_ptr.");
    SENSE_MB_CHECK((cid_info->param_key != NULL), ESP_ERR_INVALID_STATE, "incorrect cid table param_key or not initialized.");
    SENSE_MB_CHECK((cid_info->cid == cid), ESP_ERR_INVALID_STATE, "incorrect cid in table or not initialized.");

    uint8_t* value_ptr = (uint8_t*)cid_info->instance_ptr;
    // Set the instance value of the characteristic to the value
    memcpy((void*)value_ptr, (void*)value, cid_info->instance_size);

    uint8_t type = 0;
    // Set modbus parameter according to value of characteristic
    esp_err_t error = mbc_master_set_parameter(cid, (char*)cid_info->param_key, value_ptr, &type);
    SENSE_MB_CHECK((cid_info->instance_type == type), ESP_ERR_NOT_FOUND, "incorrect type of parameter (%u)", type);
    SENSE_MB_CHECK((type <= PARAM_TYPE_ASCII), ESP_ERR_NOT_SUPPORTED, "returned data type is not supported (%u)", type);
    cid_info->change_flag = 0x55; // Set value changed flag to inform higher level
    cid_info->status = error; // Keep last read/write status of cid in the information table
    cid_info->timestamp = sense_modbus_get_time_stamp_us(); // Set time stamp of last access to cid
    return error;
}