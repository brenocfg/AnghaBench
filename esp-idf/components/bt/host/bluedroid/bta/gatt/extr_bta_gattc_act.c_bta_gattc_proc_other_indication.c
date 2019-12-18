#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  value; int /*<<< orphan*/  handle; } ;
struct TYPE_11__ {TYPE_1__ att_value; int /*<<< orphan*/  handle; } ;
typedef  TYPE_3__ tGATT_CL_COMPLETE ;
struct TYPE_12__ {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  value; int /*<<< orphan*/  bda; int /*<<< orphan*/  len; int /*<<< orphan*/  is_notify; } ;
typedef  TYPE_4__ tBTA_GATTC_NOTIFY ;
struct TYPE_13__ {TYPE_2__* p_rcb; int /*<<< orphan*/  bta_conn_id; int /*<<< orphan*/  bda; } ;
typedef  TYPE_5__ tBTA_GATTC_CLCB ;
typedef  int /*<<< orphan*/  tBTA_GATTC ;
typedef  scalar_t__ UINT8 ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  BTA_GATTC_NOTIF_EVT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATTC_OPTYPE_INDICATION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bta_gattc_proc_other_indication(tBTA_GATTC_CLCB *p_clcb, UINT8 op,
                                     tGATT_CL_COMPLETE *p_data,
                                     tBTA_GATTC_NOTIFY *p_notify)
{
    APPL_TRACE_DEBUG("bta_gattc_proc_other_indication check p_data->att_value.handle=%d p_data->handle=%d",
                       p_data->att_value.handle, p_data->handle);
    APPL_TRACE_DEBUG("is_notify %d", p_notify->is_notify);

    p_notify->is_notify = (op == GATTC_OPTYPE_INDICATION) ? FALSE : TRUE;
    p_notify->len = p_data->att_value.len;
    bdcpy(p_notify->bda, p_clcb->bda);
    memcpy(p_notify->value, p_data->att_value.value, p_data->att_value.len);
    p_notify->conn_id = p_clcb->bta_conn_id;

    if (p_clcb->p_rcb->p_cback) {
        (*p_clcb->p_rcb->p_cback)(BTA_GATTC_NOTIF_EVT,  (tBTA_GATTC *)p_notify);
    }

}