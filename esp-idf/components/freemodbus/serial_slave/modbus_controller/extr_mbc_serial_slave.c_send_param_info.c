#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  mbs_notification_queue_handle; } ;
typedef  TYPE_1__ mb_slave_options_t ;
struct TYPE_6__ {void* mb_offset; int /*<<< orphan*/  time_stamp; int /*<<< orphan*/ * address; void* size; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ mb_param_info_t ;
typedef  int /*<<< orphan*/  mb_event_group_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {TYPE_1__ opts; } ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MB_PAR_INFO_TOUT ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MB_SLAVE_TAG ; 
 scalar_t__ errQUEUE_FULL ; 
 int /*<<< orphan*/  get_time_stamp () ; 
 TYPE_4__* mbs_interface_ptr ; 
 scalar_t__ pdTRUE ; 
 scalar_t__ xQueueSend (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t send_param_info(mb_event_group_t par_type, uint16_t mb_offset,
                                    uint8_t* par_address, uint16_t par_size)
{
    MB_SLAVE_CHECK((mbs_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Slave interface is not correctly initialized.");
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    esp_err_t error = ESP_FAIL;
    mb_param_info_t par_info;
    // Check if queue is not full the send parameter information
    par_info.type = par_type;
    par_info.size = par_size;
    par_info.address = par_address;
    par_info.time_stamp = get_time_stamp();
    par_info.mb_offset = mb_offset;
    BaseType_t status = xQueueSend(mbs_opts->mbs_notification_queue_handle,
                                    &par_info, MB_PAR_INFO_TOUT);
    if (pdTRUE == status) {
        ESP_LOGD(MB_SLAVE_TAG, "Queue send parameter info (type, address, size): %d, 0x%.4x, %d",
                par_type, (uint32_t)par_address, par_size);
        error = ESP_OK;
    } else if (errQUEUE_FULL == status) {
        ESP_LOGD(MB_SLAVE_TAG, "Parameter queue is overflowed.");
    }
    return error;
}