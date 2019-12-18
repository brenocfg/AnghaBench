#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_5__ {scalar_t__ scan_duplicate_filter; scalar_t__ scan_type; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ tBTM_BLE_INQ_CB ;
struct TYPE_4__ {TYPE_2__ inq_var; } ;
struct TYPE_6__ {TYPE_1__ ble_ctr_cb; } ;

/* Variables and functions */
 scalar_t__ BTM_BLE_DUPLICATE_DISABLE ; 
 scalar_t__ BTM_BLE_DUPLICATE_MAX ; 
 int /*<<< orphan*/  BTM_BLE_SCANNING ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_ENABLE ; 
 scalar_t__ BTM_BLE_SCAN_MODE_ACTI ; 
 int /*<<< orphan*/  BTM_BLE_STATE_ACTIVE_SCAN_BIT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_PASSIVE_SCAN_BIT ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int /*<<< orphan*/  OSI_SEM_MAX_TIMEOUT ; 
 int /*<<< orphan*/  btm_ble_set_topology_mask (int /*<<< orphan*/ ) ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_ble_set_scan_enable (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_sem_take (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_enable_lock ; 
 int /*<<< orphan*/  scan_enable_sem ; 
 scalar_t__ scan_enable_status ; 

tBTM_STATUS btm_ble_start_scan(void)
{
    tBTM_BLE_INQ_CB *p_inq = &btm_cb.ble_ctr_cb.inq_var;
    tBTM_STATUS status = BTM_CMD_STARTED;

    osi_mutex_lock(&scan_enable_lock, OSI_MUTEX_MAX_TIMEOUT);

    if(p_inq->scan_duplicate_filter > BTM_BLE_DUPLICATE_MAX) {
        p_inq->scan_duplicate_filter = BTM_BLE_DUPLICATE_DISABLE;
    }
    /* start scan, disable duplicate filtering */
    if (!btsnd_hcic_ble_set_scan_enable (BTM_BLE_SCAN_ENABLE, p_inq->scan_duplicate_filter)) {
        status = BTM_NO_RESOURCES;
    } else {
        osi_sem_take(&scan_enable_sem, OSI_SEM_MAX_TIMEOUT);
        if(scan_enable_status != BTM_SUCCESS) {
            status = BTM_NO_RESOURCES;
        }
        btm_cb.ble_ctr_cb.inq_var.state = BTM_BLE_SCANNING;
        if (p_inq->scan_type == BTM_BLE_SCAN_MODE_ACTI) {
            btm_ble_set_topology_mask(BTM_BLE_STATE_ACTIVE_SCAN_BIT);
        } else {
            btm_ble_set_topology_mask(BTM_BLE_STATE_PASSIVE_SCAN_BIT);
        }
    }
    osi_mutex_unlock(&scan_enable_lock);
    return status;
}