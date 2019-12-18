#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_GATTC_RCB ;
struct TYPE_23__ {int /*<<< orphan*/  client_if; } ;
struct TYPE_22__ {int /*<<< orphan*/  client_if; } ;
struct TYPE_24__ {TYPE_2__ int_conn; TYPE_1__ api_dereg; } ;
typedef  TYPE_3__ tBTA_GATTC_DATA ;
typedef  int /*<<< orphan*/  tBTA_GATTC_CLCB ;
typedef  int /*<<< orphan*/  tBTA_GATTC_CB ;
struct TYPE_25__ {int event; int /*<<< orphan*/  layer_specific; } ;
typedef  TYPE_4__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
#define  BTA_GATTC_API_BROADCAST_EVT 140 
#define  BTA_GATTC_API_CACHE_ASSOC_EVT 139 
#define  BTA_GATTC_API_CACHE_CLEAN_EVT 138 
#define  BTA_GATTC_API_CACHE_GET_ADDR_LIST_EVT 137 
#define  BTA_GATTC_API_CANCEL_OPEN_EVT 136 
#define  BTA_GATTC_API_DEREG_EVT 135 
#define  BTA_GATTC_API_DISABLE_EVT 134 
#define  BTA_GATTC_API_LISTEN_EVT 133 
#define  BTA_GATTC_API_OPEN_EVT 132 
#define  BTA_GATTC_API_REFRESH_EVT 131 
#define  BTA_GATTC_API_REG_EVT 130 
#define  BTA_GATTC_ENC_CMPL_EVT 129 
 int BTA_GATTC_INT_CONN_EVT ; 
 int BTA_GATTC_INT_DISCONN_EVT ; 
#define  BTA_GATTC_INT_START_IF_EVT 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_gattc_broadcast (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_cb ; 
 int /*<<< orphan*/ * bta_gattc_cl_get_regcb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_gattc_conncback (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_deregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_gattc_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_gattc_disconncback (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * bta_gattc_find_clcb_by_conn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bta_gattc_find_int_conn_clcb (TYPE_3__*) ; 
 int /*<<< orphan*/ * bta_gattc_find_int_disconn_clcb (TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_listen (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_process_api_cache_assoc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_process_api_cache_clean (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_process_api_cache_get_addr_list (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_process_api_open (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_process_api_open_cancel (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_process_api_refresh (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_process_enc_cmpl (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_sm_execute (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_start_if (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  gattc_evt_code (int) ; 

BOOLEAN bta_gattc_hdl_event(BT_HDR *p_msg)
{
    tBTA_GATTC_CB *p_cb = &bta_gattc_cb;
    tBTA_GATTC_CLCB *p_clcb = NULL;
    tBTA_GATTC_RCB      *p_clreg;
    BOOLEAN             rt = TRUE;
#if BTA_GATT_DEBUG == TRUE
    APPL_TRACE_DEBUG("bta_gattc_hdl_event: Event [%s]\n", gattc_evt_code(p_msg->event));
#endif
    switch (p_msg->event) {
    case BTA_GATTC_API_DISABLE_EVT:
        bta_gattc_disable(p_cb);
        break;

    case BTA_GATTC_API_REG_EVT:
        bta_gattc_register(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;

    case BTA_GATTC_INT_START_IF_EVT:
        bta_gattc_start_if(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;

    case BTA_GATTC_API_DEREG_EVT:
        p_clreg = bta_gattc_cl_get_regcb(((tBTA_GATTC_DATA *)p_msg)->api_dereg.client_if);
        bta_gattc_deregister(p_cb, p_clreg);
        break;

    case BTA_GATTC_API_OPEN_EVT:
        bta_gattc_process_api_open(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;

    case BTA_GATTC_API_CANCEL_OPEN_EVT:
        bta_gattc_process_api_open_cancel(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;

    case BTA_GATTC_API_REFRESH_EVT:
        bta_gattc_process_api_refresh(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;
    case BTA_GATTC_API_CACHE_ASSOC_EVT:
        bta_gattc_process_api_cache_assoc(p_cb, (tBTA_GATTC_DATA *)p_msg);
        break;
    case BTA_GATTC_API_CACHE_GET_ADDR_LIST_EVT:
        bta_gattc_process_api_cache_get_addr_list(p_cb, (tBTA_GATTC_DATA *)p_msg);
        break;
    case BTA_GATTC_API_CACHE_CLEAN_EVT:
        bta_gattc_process_api_cache_clean(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;
#if BLE_INCLUDED == TRUE
    case BTA_GATTC_API_LISTEN_EVT:
        bta_gattc_listen(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;
    case BTA_GATTC_API_BROADCAST_EVT:
        bta_gattc_broadcast(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;
#endif

    case BTA_GATTC_ENC_CMPL_EVT:
        bta_gattc_process_enc_cmpl(p_cb, (tBTA_GATTC_DATA *) p_msg);
        break;

    default:
        if (p_msg->event == BTA_GATTC_INT_CONN_EVT) {
            p_clcb = bta_gattc_find_int_conn_clcb((tBTA_GATTC_DATA *) p_msg);
            p_clreg = bta_gattc_cl_get_regcb(((tBTA_GATTC_DATA *)p_msg)->int_conn.client_if);
            if (p_clreg != NULL){
                bta_gattc_conncback(p_clreg, (tBTA_GATTC_DATA *) p_msg);
            }

        } else if (p_msg->event == BTA_GATTC_INT_DISCONN_EVT) {
            p_clreg = bta_gattc_cl_get_regcb(((tBTA_GATTC_DATA *)p_msg)->int_conn.client_if);
            if (p_clreg != NULL){
                bta_gattc_disconncback(p_clreg, (tBTA_GATTC_DATA *) p_msg);
            }
            p_clcb = bta_gattc_find_int_disconn_clcb((tBTA_GATTC_DATA *) p_msg);
        } else {
            p_clcb = bta_gattc_find_clcb_by_conn_id(p_msg->layer_specific);
        }

        if (p_clcb != NULL) {
            rt = bta_gattc_sm_execute(p_clcb, p_msg->event, (tBTA_GATTC_DATA *) p_msg);
        } else {
            APPL_TRACE_DEBUG("Ignore unknown conn ID: %d\n", p_msg->layer_specific);
        }

        break;
    }


    return rt;
}