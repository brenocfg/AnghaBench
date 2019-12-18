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
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {size_t cid; int change_flag; int /*<<< orphan*/ * param_key; int /*<<< orphan*/ * instance_ptr; } ;
typedef  TYPE_1__ characteristic_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SENSE_MB_CHECK (int,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__** active_cid_table ; 
 size_t active_cid_table_size ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

esp_err_t sense_modbus_get_cid_data(uint16_t cid, characteristic_descriptor_t* cid_data)
{
    assert(active_cid_table != NULL);
    SENSE_MB_CHECK((cid_data != NULL), ESP_ERR_INVALID_ARG, "incorrect data pointer.");
    SENSE_MB_CHECK((cid < active_cid_table_size), ESP_ERR_INVALID_ARG, "cid is not found in the table.");

    characteristic_descriptor_t* cid_info = active_cid_table[cid];
    SENSE_MB_CHECK((cid_info != NULL), ESP_ERR_INVALID_STATE, "incorrect cid table or not initialized.");
    SENSE_MB_CHECK((cid_info->instance_ptr != NULL), ESP_ERR_INVALID_STATE, "incorrect cid table instance_ptr.");
    SENSE_MB_CHECK((cid_info->param_key != NULL), ESP_ERR_INVALID_STATE, "incorrect cid table param_key.");
    SENSE_MB_CHECK((cid_info->cid == cid), ESP_ERR_INVALID_STATE, "incorrect cid in the table or not initialized.");
    *cid_data = *cid_info; // Set cid data
    cid_info->change_flag = 0x00; // Reset flag once we get changed value

    return ESP_OK;
}