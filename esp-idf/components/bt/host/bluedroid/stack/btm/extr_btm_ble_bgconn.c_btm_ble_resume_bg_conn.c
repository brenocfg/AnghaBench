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
struct TYPE_3__ {scalar_t__ bg_conn_type; int /*<<< orphan*/  p_select_cback; } ;
typedef  TYPE_1__ tBTM_BLE_CB ;
struct TYPE_4__ {TYPE_1__ ble_ctr_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTM_BLE_CONN_AUTO ; 
 scalar_t__ BTM_BLE_CONN_NONE ; 
 scalar_t__ BTM_BLE_CONN_SELECTIVE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_start_auto_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_start_select_conn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ btm_cb ; 

BOOLEAN btm_ble_resume_bg_conn(void)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BOOLEAN ret = FALSE;

    if (p_cb->bg_conn_type != BTM_BLE_CONN_NONE) {
        if (p_cb->bg_conn_type == BTM_BLE_CONN_AUTO) {
            ret = btm_ble_start_auto_conn(TRUE);
        }

        if (p_cb->bg_conn_type == BTM_BLE_CONN_SELECTIVE) {
            ret = btm_ble_start_select_conn(TRUE, btm_cb.ble_ctr_cb.p_select_cback);
        }
    }

    return ret;
}