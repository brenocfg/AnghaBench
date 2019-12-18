#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  remote_bda; } ;
struct TYPE_13__ {TYPE_1__ api_cancel_conn; } ;
typedef  TYPE_3__ tBTA_GATTC_DATA ;
struct TYPE_14__ {TYPE_2__* p_rcb; } ;
typedef  TYPE_4__ tBTA_GATTC_CLCB ;
struct TYPE_15__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_5__ tBTA_GATTC ;
struct TYPE_12__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_5__*) ;int /*<<< orphan*/  client_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_CANCEL_OPEN_EVT ; 
 int /*<<< orphan*/  BTA_GATTC_INT_CANCEL_OPEN_OK_EVT ; 
 int /*<<< orphan*/  BTA_GATT_ERROR ; 
 scalar_t__ GATT_CancelConnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_gattc_sm_execute (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_5__*) ; 

void bta_gattc_cancel_open(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC          cb_data;

    if (GATT_CancelConnect(p_clcb->p_rcb->client_if, p_data->api_cancel_conn.remote_bda, TRUE)) {
        bta_gattc_sm_execute(p_clcb, BTA_GATTC_INT_CANCEL_OPEN_OK_EVT, p_data);
    } else {
        if ( p_clcb->p_rcb->p_cback ) {
            cb_data.status = BTA_GATT_ERROR;
            (*p_clcb->p_rcb->p_cback)(BTA_GATTC_CANCEL_OPEN_EVT, &cb_data);
        }
    }
}