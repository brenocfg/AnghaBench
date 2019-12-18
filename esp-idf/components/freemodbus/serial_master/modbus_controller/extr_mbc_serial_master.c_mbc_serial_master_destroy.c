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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  mbm_event_group; int /*<<< orphan*/  mbm_task_handle; } ;
typedef  TYPE_1__ mb_master_options_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ eMBErrorCode ;
struct TYPE_5__ {TYPE_1__ opts; } ;
typedef  int EventBits_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ MB_ENOERR ; 
 int MB_EVENT_STACK_STARTED ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ eMBMasterClose () ; 
 scalar_t__ eMBMasterDisable () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* mbm_interface_ptr ; 
 int /*<<< orphan*/  vEventGroupDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ ) ; 
 int xEventGroupClearBits (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t mbc_serial_master_destroy(void)
{
    MB_MASTER_CHECK((mbm_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Master interface uninitialized.");
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;
    eMBErrorCode mb_error = MB_ENOERR;
    // Stop polling by clearing correspondent bit in the event group
    EventBits_t flag = xEventGroupClearBits(mbm_opts->mbm_event_group,
                                    (EventBits_t)MB_EVENT_STACK_STARTED);
    MB_MASTER_CHECK((flag & MB_EVENT_STACK_STARTED),
                ESP_ERR_INVALID_STATE, "mb stack stop event failure.");
    // Desable and then destroy the Modbus stack
    mb_error = eMBMasterDisable();
    MB_MASTER_CHECK((mb_error == MB_ENOERR), ESP_ERR_INVALID_STATE, "mb stack disable failure.");
    (void)vTaskDelete(mbm_opts->mbm_task_handle);
    (void)vEventGroupDelete(mbm_opts->mbm_event_group);
    mb_error = eMBMasterClose();
    MB_MASTER_CHECK((mb_error == MB_ENOERR), ESP_ERR_INVALID_STATE,
            "mb stack close failure returned (0x%x).", (uint32_t)mb_error);
    free(mbm_interface_ptr); // free the memory allocated for options
    mbm_interface_ptr = NULL;
    return ESP_OK;
}