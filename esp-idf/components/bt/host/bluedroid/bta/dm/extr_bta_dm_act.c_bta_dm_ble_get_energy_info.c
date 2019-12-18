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
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_5__ {int /*<<< orphan*/  p_energy_info_cback; } ;
struct TYPE_6__ {TYPE_1__ ble_energy_info; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;
struct TYPE_7__ {int /*<<< orphan*/  p_energy_info_cback; } ;

/* Variables and functions */
 scalar_t__ BTM_BleGetEnergyInfo (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__)) ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  bta_ble_energy_info_cmpl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__ bta_dm_cb ; 

void bta_dm_ble_get_energy_info(tBTA_DM_MSG *p_data)
{
    tBTM_STATUS btm_status = 0;

    bta_dm_cb.p_energy_info_cback = p_data->ble_energy_info.p_energy_info_cback;
    btm_status = BTM_BleGetEnergyInfo(bta_ble_energy_info_cmpl);
    if (BTM_CMD_STARTED != btm_status) {
        bta_ble_energy_info_cmpl(0, 0, 0, 0, btm_status);
    }
}