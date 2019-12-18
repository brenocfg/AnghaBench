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
struct TYPE_4__ {scalar_t__ supervision_tout; scalar_t__ slave_latency; scalar_t__ max_conn_int; scalar_t__ min_conn_int; } ;
struct TYPE_5__ {TYPE_1__ conn_params; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_CONN_INT_MAX ; 
 int /*<<< orphan*/  BTM_BLE_CONN_INT_MIN ; 
 scalar_t__ BTM_BLE_CONN_LATENCY_MAX ; 
 scalar_t__ BTM_BLE_CONN_PARAM_UNDEF ; 
 scalar_t__ BTM_BLE_CONN_SLAVE_LATENCY_DEF ; 
 int /*<<< orphan*/  BTM_BLE_CONN_SUP_TOUT_MAX ; 
 int /*<<< orphan*/  BTM_BLE_CONN_SUP_TOUT_MIN ; 
 scalar_t__ BTM_BLE_CONN_TIMEOUT_DEF ; 
 scalar_t__ BTM_BLE_ISVALID_PARAM (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 TYPE_2__* btm_find_or_alloc_dev (int /*<<< orphan*/ ) ; 

void BTM_BleSetPrefConnParams (BD_ADDR bd_addr,
                               UINT16 min_conn_int, UINT16 max_conn_int,
                               UINT16 slave_latency, UINT16 supervision_tout)
{
    tBTM_SEC_DEV_REC  *p_dev_rec = btm_find_or_alloc_dev (bd_addr);

    BTM_TRACE_API ("BTM_BleSetPrefConnParams min: %u  max: %u  latency: %u  \
                    tout: %u",
                   min_conn_int, max_conn_int, slave_latency, supervision_tout);

    if (BTM_BLE_ISVALID_PARAM(min_conn_int, BTM_BLE_CONN_INT_MIN, BTM_BLE_CONN_INT_MAX) &&
            BTM_BLE_ISVALID_PARAM(max_conn_int, BTM_BLE_CONN_INT_MIN, BTM_BLE_CONN_INT_MAX) &&
            BTM_BLE_ISVALID_PARAM(supervision_tout, BTM_BLE_CONN_SUP_TOUT_MIN, BTM_BLE_CONN_SUP_TOUT_MAX) &&
            (slave_latency <= BTM_BLE_CONN_LATENCY_MAX || slave_latency == BTM_BLE_CONN_PARAM_UNDEF)) {
        if (p_dev_rec) {
            /* expect conn int and stout and slave latency to be updated all together */
            if (min_conn_int != BTM_BLE_CONN_PARAM_UNDEF || max_conn_int != BTM_BLE_CONN_PARAM_UNDEF) {
                if (min_conn_int != BTM_BLE_CONN_PARAM_UNDEF) {
                    p_dev_rec->conn_params.min_conn_int = min_conn_int;
                } else {
                    p_dev_rec->conn_params.min_conn_int = max_conn_int;
                }

                if (max_conn_int != BTM_BLE_CONN_PARAM_UNDEF) {
                    p_dev_rec->conn_params.max_conn_int = max_conn_int;
                } else {
                    p_dev_rec->conn_params.max_conn_int = min_conn_int;
                }

                if (slave_latency != BTM_BLE_CONN_PARAM_UNDEF) {
                    p_dev_rec->conn_params.slave_latency = slave_latency;
                } else {
                    p_dev_rec->conn_params.slave_latency = BTM_BLE_CONN_SLAVE_LATENCY_DEF;
                }

                if (supervision_tout != BTM_BLE_CONN_PARAM_UNDEF) {
                    p_dev_rec->conn_params.supervision_tout = supervision_tout;
                } else {
                    p_dev_rec->conn_params.supervision_tout = BTM_BLE_CONN_TIMEOUT_DEF;
                }

            }

        } else {
            BTM_TRACE_ERROR("Unknown Device, setting rejected");
        }
    } else {
        BTM_TRACE_ERROR("Illegal Connection Parameters");
    }
}