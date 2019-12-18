#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  mb_param_type; int /*<<< orphan*/  mb_size; int /*<<< orphan*/  mb_reg_start; int /*<<< orphan*/  mb_slave_addr; scalar_t__ param_key; } ;
typedef  TYPE_1__ mb_parameter_descriptor_t ;
struct TYPE_8__ {int /*<<< orphan*/  command; int /*<<< orphan*/  reg_size; int /*<<< orphan*/  reg_start; int /*<<< orphan*/  slave_addr; } ;
typedef  TYPE_2__ mb_param_request_t ;
typedef  int /*<<< orphan*/  mb_param_mode_t ;
struct TYPE_9__ {scalar_t__ mbm_param_descriptor_size; TYPE_1__* mbm_param_descriptor_table; } ;
typedef  TYPE_3__ mb_master_options_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_10__ {TYPE_3__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MB_MASTER_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MB_PARAM_WRITE ; 
 int /*<<< orphan*/  mbc_serial_master_get_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* mbm_interface_ptr ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static esp_err_t mbc_serial_master_set_request(char* name, mb_param_mode_t mode, 
                                                mb_param_request_t* request,
                                                mb_parameter_descriptor_t* reg_data)
{
    MB_MASTER_CHECK((mbm_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Master interface uninitialized.");
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;
    esp_err_t error = ESP_ERR_NOT_FOUND;
    MB_MASTER_CHECK((name != NULL), 
                        ESP_ERR_INVALID_ARG, "mb incorrect parameter name.");
    MB_MASTER_CHECK((request != NULL), 
                        ESP_ERR_INVALID_ARG, "mb incorrect request parameter.");
    MB_MASTER_CHECK((mode <= MB_PARAM_WRITE), 
                        ESP_ERR_INVALID_ARG, "mb incorrect mode.");
    MB_MASTER_ASSERT(mbm_opts->mbm_param_descriptor_table != NULL);
    const mb_parameter_descriptor_t* reg_ptr = mbm_opts->mbm_param_descriptor_table;
    for (uint16_t counter = 0; counter < (mbm_opts->mbm_param_descriptor_size); counter++, reg_ptr++)
    {
        // Check the cid of the parameter is equal to record number in the table
        // Check the length of name and parameter key strings from table
        size_t param_key_len = strlen((const char*)reg_ptr->param_key);
        if (param_key_len != strlen((const char*)name)) {
            continue; // The length of strings is different then check next record in the table
        }
        // Compare the name of parameter with parameter key from table
        uint8_t comp_result = memcmp((const char*)name, (const char*)reg_ptr->param_key, (size_t)param_key_len);
        if (comp_result == 0) {
            // The correct line is found in the table and reg_ptr points to the found parameter description
            request->slave_addr = reg_ptr->mb_slave_addr;
            request->reg_start = reg_ptr->mb_reg_start;
            request->reg_size = reg_ptr->mb_size;
            request->command = mbc_serial_master_get_command(reg_ptr->mb_param_type, mode);
            MB_MASTER_CHECK((request->command > 0), 
                                ESP_ERR_INVALID_ARG, 
                                "mb incorrect command or parameter type.");
            if (reg_data != NULL) {
                *reg_data = *reg_ptr; // Set the cid registered parameter data
            }
            error = ESP_OK;
            break;
        }
    }
    return error;
}