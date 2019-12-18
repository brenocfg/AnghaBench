#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ esp_gattc_cb_event_t ;
typedef  scalar_t__ esp_gatt_if_t ;
struct TYPE_6__ {scalar_t__ status; size_t app_id; } ;
struct TYPE_7__ {TYPE_1__ reg; } ;
typedef  TYPE_2__ esp_ble_gattc_cb_param_t ;
struct TYPE_8__ {scalar_t__ gattc_if; int /*<<< orphan*/  (* gattc_cb ) (scalar_t__,scalar_t__,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_TAG ; 
 scalar_t__ ESP_GATTC_REG_EVT ; 
 scalar_t__ ESP_GATT_IF_NONE ; 
 scalar_t__ ESP_GATT_OK ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,size_t,scalar_t__) ; 
 int GATTC_PROFILE_NUM ; 
 TYPE_4__* gattc_profile_tab ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,TYPE_2__*) ; 

__attribute__((used)) static void esp_gattc_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param)
{
    /* If event is register event, store the gattc_if for each profile */
    if (event == ESP_GATTC_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            gattc_profile_tab[param->reg.app_id].gattc_if = gattc_if;
        } else {
            ESP_LOGI(COEX_TAG, "reg app failed, app_id %04x, status %d\n",
                    param->reg.app_id,
                    param->reg.status);
            return;
        }
    }

    /* If the gattc_if equal to profile A, call profile A cb handler,
     * so here call each profile's callback */
    do {
        int idx;
        for (idx = 0; idx < GATTC_PROFILE_NUM; idx ++) {
            if (gattc_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
                    gattc_if == gattc_profile_tab[idx].gattc_if) {
                if (gattc_profile_tab[idx].gattc_cb) {
                    gattc_profile_tab[idx].gattc_cb(event, gattc_if, param);
                }
            }
        }
    } while (0);
}