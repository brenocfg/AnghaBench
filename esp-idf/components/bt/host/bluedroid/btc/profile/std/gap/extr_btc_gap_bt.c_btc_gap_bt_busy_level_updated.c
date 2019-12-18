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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__ disc_st_chg; } ;
typedef  TYPE_2__ esp_bt_gap_cb_param_t ;

/* Variables and functions */
 scalar_t__ BTM_BL_INQUIRY_CANCELLED ; 
 scalar_t__ BTM_BL_INQUIRY_COMPLETE ; 
 scalar_t__ BTM_BL_INQUIRY_STARTED ; 
 int /*<<< orphan*/  ESP_BT_GAP_DISCOVERY_STARTED ; 
 int /*<<< orphan*/  ESP_BT_GAP_DISCOVERY_STOPPED ; 
 int /*<<< orphan*/  ESP_BT_GAP_DISC_STATE_CHANGED_EVT ; 
 int /*<<< orphan*/  btc_gap_bt_cb_to_app (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int btc_gap_bt_inquiry_in_progress ; 

void btc_gap_bt_busy_level_updated(uint8_t bl_flags)
{
    esp_bt_gap_cb_param_t param;

    if (bl_flags == BTM_BL_INQUIRY_STARTED) {
        param.disc_st_chg.state = ESP_BT_GAP_DISCOVERY_STARTED;
        btc_gap_bt_cb_to_app(ESP_BT_GAP_DISC_STATE_CHANGED_EVT, &param);
        btc_gap_bt_inquiry_in_progress = true;
    } else if (bl_flags == BTM_BL_INQUIRY_CANCELLED ||
               bl_flags == BTM_BL_INQUIRY_COMPLETE) {
        param.disc_st_chg.state = ESP_BT_GAP_DISCOVERY_STOPPED;
        btc_gap_bt_cb_to_app(ESP_BT_GAP_DISC_STATE_CHANGED_EVT, &param);
        btc_gap_bt_inquiry_in_progress = false;
    }
}