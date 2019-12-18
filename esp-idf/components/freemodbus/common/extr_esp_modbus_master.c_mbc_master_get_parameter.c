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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {scalar_t__ (* get_parameter ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  esp_err_to_name (scalar_t__) ; 
 TYPE_1__* master_interface_ptr ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

esp_err_t mbc_master_get_parameter(uint16_t cid, char* name, uint8_t* value, uint8_t* type)
{
    esp_err_t error = ESP_OK;
    MB_MASTER_CHECK((master_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Master interface is not correctly initialized.");
    MB_MASTER_CHECK((master_interface_ptr->get_parameter != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Master interface is not correctly initialized.");
    error = master_interface_ptr->get_parameter(cid, name, value, type);
    MB_MASTER_CHECK((error == ESP_OK), 
                    error,
                    "SERIAL master get parameter failure error=(0x%x) (%s).",
                    error, esp_err_to_name(error));
    return error;
}