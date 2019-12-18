#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/ * param_key; } ;
typedef  TYPE_1__ mb_parameter_descriptor_t ;
struct TYPE_6__ {size_t mbm_param_descriptor_size; TYPE_1__* mbm_param_descriptor_table; } ;
typedef  TYPE_2__ mb_master_options_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {TYPE_2__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* mbm_interface_ptr ; 

__attribute__((used)) static esp_err_t mbc_serial_master_get_cid_info(uint16_t cid, const mb_parameter_descriptor_t** param_buffer)
{
    MB_MASTER_CHECK((mbm_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Master interface uninitialized.");
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;

    MB_MASTER_CHECK((param_buffer != NULL), 
                        ESP_ERR_INVALID_ARG, "mb incorrect data buffer pointer.");
    MB_MASTER_CHECK((mbm_opts->mbm_param_descriptor_table != NULL), 
                        ESP_ERR_INVALID_ARG, "mb incorrect descriptor table or not set.");
    MB_MASTER_CHECK((cid < mbm_opts->mbm_param_descriptor_size), 
                        ESP_ERR_NOT_FOUND, "mb incorrect cid of characteristic.");

    // It is assumed that characteristics cid increased in the table
    const mb_parameter_descriptor_t* reg_info = &mbm_opts->mbm_param_descriptor_table[cid];

    MB_MASTER_CHECK((reg_info->param_key != NULL), 
                        ESP_ERR_INVALID_ARG, "mb incorrect characteristic key.");
    *param_buffer = reg_info;
    return ESP_OK;
}