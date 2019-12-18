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
typedef  int /*<<< orphan*/  tGATT_IF ;
struct TYPE_8__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_9__ {int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  client_if; TYPE_1__ hdr; } ;
struct TYPE_10__ {TYPE_2__ enc_cmpl; } ;
typedef  TYPE_3__ tBTA_GATTC_DATA ;
struct TYPE_11__ {int /*<<< orphan*/  bta_conn_id; } ;
typedef  TYPE_4__ tBTA_GATTC_CLCB ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTC_ENC_CMPL_EVT ; 
 int /*<<< orphan*/  BTA_GATT_TRANSPORT_LE ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* bta_gattc_find_clcb_by_cif (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_hh_le_is_hh_gatt_if (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_calloc (int) ; 

__attribute__((used)) static void bta_gattc_enc_cmpl_cback(tGATT_IF gattc_if, BD_ADDR bda)
{
    tBTA_GATTC_DATA *p_buf;
    tBTA_GATTC_CLCB *p_clcb = NULL;

    if ((p_clcb = bta_gattc_find_clcb_by_cif(gattc_if, bda, BTA_GATT_TRANSPORT_LE)) == NULL) {
        return;
    }

#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
    /* filter this event just for BTA HH LE GATT client,
       In the future, if we want to enable encryption complete event
       for all GATT clients, we can remove this code */
    if (!bta_hh_le_is_hh_gatt_if(gattc_if)) {
        return;
    }
#endif

    APPL_TRACE_DEBUG("bta_gattc_enc_cmpl_cback: cif = %d", gattc_if);

    if ((p_buf = (tBTA_GATTC_DATA *) osi_calloc(sizeof(tBTA_GATTC_DATA))) != NULL) {
        memset(p_buf, 0, sizeof(tBTA_GATTC_DATA));

        p_buf->enc_cmpl.hdr.event            = BTA_GATTC_ENC_CMPL_EVT;
        p_buf->enc_cmpl.hdr.layer_specific   = p_clcb->bta_conn_id;
        p_buf->enc_cmpl.client_if            = gattc_if;
        bdcpy(p_buf->enc_cmpl.remote_bda, bda);

        bta_sys_sendmsg(p_buf);
    }
}