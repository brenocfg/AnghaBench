#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mb_param_info_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {scalar_t__ (* get_param_info ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* slave_interface_ptr ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

esp_err_t mbc_slave_get_param_info(mb_param_info_t* reg_info, uint32_t timeout)
{
    esp_err_t error = ESP_OK;
    MB_SLAVE_CHECK((slave_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Slave interface is not correctly initialized.");
    MB_SLAVE_CHECK((slave_interface_ptr->get_param_info != NULL), 
                    ESP_ERR_INVALID_STATE,
                    "Slave interface is not correctly initialized.");
    error = slave_interface_ptr->get_param_info(reg_info, timeout);
    MB_SLAVE_CHECK((error == ESP_OK), 
                    ESP_ERR_INVALID_STATE, 
                    "SERIAL slave get parameter info failure error=(0x%x).", error);
    return error;
}