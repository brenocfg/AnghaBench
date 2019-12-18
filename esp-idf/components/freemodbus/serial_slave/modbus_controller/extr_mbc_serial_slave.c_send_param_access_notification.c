#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  mbs_event_group; } ;
typedef  TYPE_1__ mb_slave_options_t ;
typedef  int mb_event_group_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {TYPE_1__ opts; } ;
typedef  int /*<<< orphan*/  EventBits_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MB_SLAVE_TAG ; 
 TYPE_2__* mbs_interface_ptr ; 
 int /*<<< orphan*/  xEventGroupSetBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t send_param_access_notification(mb_event_group_t event)
{
    MB_SLAVE_CHECK((mbs_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Slave interface is not correctly initialized.");
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    esp_err_t err = ESP_FAIL;
    mb_event_group_t bits = (mb_event_group_t)xEventGroupSetBits(mbs_opts->mbs_event_group,
                                                                    (EventBits_t)event);
    if (bits & event) {
        ESP_LOGD(MB_SLAVE_TAG, "The MB_REG_CHANGE_EVENT = 0x%.2x is set.", (uint8_t)event);
        err = ESP_OK;
    }
    return err;
}