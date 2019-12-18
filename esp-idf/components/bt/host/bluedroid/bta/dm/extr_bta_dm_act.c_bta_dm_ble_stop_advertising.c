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
struct TYPE_4__ {scalar_t__ event; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 scalar_t__ BTA_DM_API_BLE_STOP_ADV_EVT ; 
 int /*<<< orphan*/  btm_ble_stop_adv () ; 

void bta_dm_ble_stop_advertising(tBTA_DM_MSG *p_data)
{
    if (p_data->hdr.event != BTA_DM_API_BLE_STOP_ADV_EVT) {
        APPL_TRACE_ERROR("Invalid BTA event,can't stop the BLE adverting\n");
    }

    btm_ble_stop_adv();
}