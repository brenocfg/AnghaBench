#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_7__ {scalar_t__ ble_evt_type; } ;
struct TYPE_8__ {TYPE_1__ results; } ;
typedef  TYPE_2__ tBTM_INQ_INFO ;
struct TYPE_9__ {int /*<<< orphan*/  rmt_name_timer_ent; int /*<<< orphan*/  remname_bda; scalar_t__ remname_active; int /*<<< orphan*/ * p_remname_cmpl_cb; } ;
typedef  TYPE_3__ tBTM_INQUIRY_VAR_ST ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
struct TYPE_11__ {TYPE_3__ btm_inq_vars; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* supports_ble ) () ;} ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_BLE_EVT_CONN_ADV ; 
 scalar_t__ BTM_BLE_EVT_CONN_DIR_ADV ; 
 int /*<<< orphan*/  BTM_BUSY ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_EXT_BLE_RMT_NAME_TIMEOUT ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTU_TTYPE_BTM_RMT_NAME ; 
 int /*<<< orphan*/  GAP_BleReadPeerDevName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  btm_ble_read_remote_name_cmpl ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* controller_get_interface () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

tBTM_STATUS btm_ble_read_remote_name(BD_ADDR remote_bda, tBTM_INQ_INFO *p_cur, tBTM_CMPL_CB *p_cb)
{
    tBTM_INQUIRY_VAR_ST      *p_inq = &btm_cb.btm_inq_vars;

    if (!controller_get_interface()->supports_ble()) {
        return BTM_ERR_PROCESSING;
    }

    if (p_cur &&
            p_cur->results.ble_evt_type != BTM_BLE_EVT_CONN_ADV &&
            p_cur->results.ble_evt_type != BTM_BLE_EVT_CONN_DIR_ADV) {
        BTM_TRACE_DEBUG("name request to non-connectable device failed.");
        return BTM_ERR_PROCESSING;
    }

    /* read remote device name using GATT procedure */
    if (p_inq->remname_active) {
        return BTM_BUSY;
    }

#if (defined(GAP_INCLUDED) && GAP_INCLUDED == TRUE && GATTS_INCLUDED == TRUE)
    if (!GAP_BleReadPeerDevName(remote_bda, btm_ble_read_remote_name_cmpl)) {
        return BTM_BUSY;
    }
#endif

    p_inq->p_remname_cmpl_cb = p_cb;
    p_inq->remname_active = TRUE;

    memcpy(p_inq->remname_bda, remote_bda, BD_ADDR_LEN);

    btu_start_timer (&p_inq->rmt_name_timer_ent,
                     BTU_TTYPE_BTM_RMT_NAME,
                     BTM_EXT_BLE_RMT_NAME_TIMEOUT);

    return BTM_CMD_STARTED;
}