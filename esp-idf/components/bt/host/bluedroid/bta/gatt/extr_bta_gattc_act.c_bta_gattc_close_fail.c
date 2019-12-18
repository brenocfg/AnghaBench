#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  layer_specific; } ;
struct TYPE_14__ {TYPE_1__ hdr; } ;
typedef  TYPE_4__ tBTA_GATTC_DATA ;
struct TYPE_15__ {TYPE_3__* p_rcb; int /*<<< orphan*/  bda; } ;
typedef  TYPE_5__ tBTA_GATTC_CLCB ;
struct TYPE_12__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  status; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  client_if; } ;
struct TYPE_16__ {TYPE_2__ close; } ;
typedef  TYPE_6__ tBTA_GATTC ;
struct TYPE_13__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_6__*) ;int /*<<< orphan*/  client_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_CLOSE_EVT ; 
 int /*<<< orphan*/  BTA_GATT_CONN_NONE ; 
 int /*<<< orphan*/  BTA_GATT_ERROR ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__*) ; 

void bta_gattc_close_fail(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATTC           cb_data;

    if ( p_clcb->p_rcb->p_cback ) {
        memset(&cb_data, 0, sizeof(tBTA_GATTC));
        cb_data.close.client_if = p_clcb->p_rcb->client_if;
        cb_data.close.conn_id   = p_data->hdr.layer_specific;
        bdcpy(cb_data.close.remote_bda, p_clcb->bda);
        cb_data.close.status    = BTA_GATT_ERROR;
        cb_data.close.reason    = BTA_GATT_CONN_NONE;


        (*p_clcb->p_rcb->p_cback)(BTA_GATTC_CLOSE_EVT, &cb_data);
    }
}