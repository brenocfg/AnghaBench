#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  is_direct; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  client_if; } ;
struct TYPE_9__ {int /*<<< orphan*/  layer_specific; } ;
struct TYPE_10__ {TYPE_1__ api_conn; TYPE_2__ hdr; } ;
typedef  TYPE_3__ tBTA_GATTC_DATA ;
struct TYPE_11__ {int /*<<< orphan*/  bta_conn_id; } ;
typedef  TYPE_4__ tBTA_GATTC_CLCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTA_GATTC_API_OPEN_EVT ; 
 int /*<<< orphan*/  BTA_GATT_TRANSPORT_LE ; 
 scalar_t__ FALSE ; 
 scalar_t__ GATT_GetConnIdIfConnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* bta_gattc_clcb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_gattc_sm_execute (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_gattc_init_clcb_conn(UINT8 cif, BD_ADDR remote_bda)
{
    tBTA_GATTC_CLCB     *p_clcb = NULL;
    tBTA_GATTC_DATA     gattc_data;
    UINT16              conn_id;

    /* should always get the connection ID */
    if (GATT_GetConnIdIfConnected(cif, remote_bda, &conn_id, BTA_GATT_TRANSPORT_LE) == FALSE) {
        APPL_TRACE_ERROR("bta_gattc_init_clcb_conn ERROR: not a connected device");
        return;
    }

    /* initaite a new connection here */
    if ((p_clcb = bta_gattc_clcb_alloc(cif, remote_bda, BTA_GATT_TRANSPORT_LE)) != NULL) {
        gattc_data.hdr.layer_specific = p_clcb->bta_conn_id = conn_id;

        gattc_data.api_conn.client_if = cif;
        memcpy(gattc_data.api_conn.remote_bda, remote_bda, BD_ADDR_LEN);
        gattc_data.api_conn.is_direct = TRUE;

        bta_gattc_sm_execute(p_clcb, BTA_GATTC_API_OPEN_EVT, &gattc_data);
    } else {
        APPL_TRACE_ERROR("No resources");
    }
}