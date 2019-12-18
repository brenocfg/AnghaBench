#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
typedef  TYPE_1__ tBTA_GATTC_RCB ;
struct TYPE_8__ {int /*<<< orphan*/  client_if; int /*<<< orphan*/  remote_bda; } ;
typedef  TYPE_2__ tBTA_GATTC_API_CANCEL_OPEN ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ tBTA_GATTC ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTA_GATTC_CANCEL_OPEN_EVT ; 
 int /*<<< orphan*/  BTA_GATT_ERROR ; 
 int /*<<< orphan*/  BTA_GATT_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATT_CancelConnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* bta_gattc_cl_get_regcb (int /*<<< orphan*/ ) ; 
 scalar_t__ bta_gattc_mark_bg_conn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

void bta_gattc_cancel_bk_conn(tBTA_GATTC_API_CANCEL_OPEN *p_data)
{
    tBTA_GATTC_RCB      *p_clreg;
    tBTA_GATTC          cb_data;
    cb_data.status = BTA_GATT_ERROR;

    /* remove the device from the bg connection mask */
    if (bta_gattc_mark_bg_conn(p_data->client_if, p_data->remote_bda, FALSE, FALSE)) {
        if (GATT_CancelConnect(p_data->client_if, p_data->remote_bda, FALSE)) {
            cb_data.status = BTA_GATT_OK;
        } else {
            APPL_TRACE_ERROR("bta_gattc_cancel_bk_conn failed");
        }
    }
    p_clreg = bta_gattc_cl_get_regcb(p_data->client_if);

    if (p_clreg && p_clreg->p_cback) {
        (*p_clreg->p_cback)(BTA_GATTC_CANCEL_OPEN_EVT, &cb_data);
    }

}