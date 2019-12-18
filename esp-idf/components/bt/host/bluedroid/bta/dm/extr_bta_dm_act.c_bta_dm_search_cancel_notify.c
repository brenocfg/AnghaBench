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
typedef  int /*<<< orphan*/  tBTA_DM_MSG ;
struct TYPE_2__ {int /*<<< orphan*/  peer_bdaddr; scalar_t__ gatt_disc_active; int /*<<< orphan*/  name_discover_done; int /*<<< orphan*/  (* p_search_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_SEARCH_CANCEL_CMPL_EVT ; 
 int /*<<< orphan*/  BTM_CancelRemoteDeviceName () ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_dm_cancel_gatt_discovery (int /*<<< orphan*/ ) ; 
 TYPE_1__ bta_dm_search_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bta_dm_search_cancel_notify (tBTA_DM_MSG *p_data)
{
    UNUSED(p_data);
    if (bta_dm_search_cb.p_search_cback) {
        bta_dm_search_cb.p_search_cback(BTA_DM_SEARCH_CANCEL_CMPL_EVT, NULL);
    }
    if (!bta_dm_search_cb.name_discover_done) {
        BTM_CancelRemoteDeviceName();
    }
#if (BLE_INCLUDED == TRUE) && (BTA_GATT_INCLUDED == TRUE) && (SDP_INCLUDED == TRUE) && (GATTC_INCLUDED) == TRUE
    if (bta_dm_search_cb.gatt_disc_active) {
        bta_dm_cancel_gatt_discovery(bta_dm_search_cb.peer_bdaddr);
    }
#endif

}