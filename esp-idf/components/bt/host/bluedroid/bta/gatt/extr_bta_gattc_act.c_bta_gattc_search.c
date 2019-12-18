#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_GATT_STATUS ;
struct TYPE_12__ {int /*<<< orphan*/  p_srvc_uuid; } ;
struct TYPE_16__ {TYPE_1__ api_search; } ;
typedef  TYPE_5__ tBTA_GATTC_DATA ;
struct TYPE_17__ {TYPE_3__* p_rcb; int /*<<< orphan*/  searched_service_source; int /*<<< orphan*/  bta_conn_id; TYPE_4__* p_srcb; } ;
typedef  TYPE_6__ tBTA_GATTC_CLCB ;
struct TYPE_13__ {int /*<<< orphan*/  searched_service_source; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  status; } ;
struct TYPE_18__ {TYPE_2__ search_cmpl; } ;
typedef  TYPE_7__ tBTA_GATTC ;
struct TYPE_15__ {scalar_t__ p_srvc_cache; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_7__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTC_SEARCH_CMPL_EVT ; 
 int /*<<< orphan*/  BTA_GATT_OK ; 
 int /*<<< orphan*/  GATT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  bta_gattc_search_service (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_7__*) ; 

void bta_gattc_search(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    tBTA_GATT_STATUS    status = GATT_INTERNAL_ERROR;
    tBTA_GATTC cb_data;
    APPL_TRACE_DEBUG("bta_gattc_search conn_id=%d", p_clcb->bta_conn_id);
    if (p_clcb->p_srcb && p_clcb->p_srcb->p_srvc_cache) {
        status = BTA_GATT_OK;
        /* search the local cache of a server device */
        bta_gattc_search_service(p_clcb, p_data->api_search.p_srvc_uuid);
    }
    cb_data.search_cmpl.status  = status;
    cb_data.search_cmpl.conn_id = p_clcb->bta_conn_id;
    cb_data.search_cmpl.searched_service_source = p_clcb->searched_service_source;

    /* end of search or no server cache available */
    ( *p_clcb->p_rcb->p_cback)(BTA_GATTC_SEARCH_CMPL_EVT,  &cb_data);
}