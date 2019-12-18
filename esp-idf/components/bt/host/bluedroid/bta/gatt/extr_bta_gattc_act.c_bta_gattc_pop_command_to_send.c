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
struct TYPE_13__ {int /*<<< orphan*/  event; } ;
struct TYPE_16__ {TYPE_2__ hdr; } ;
typedef  TYPE_5__ tBTA_GATTC_DATA ;
struct TYPE_17__ {TYPE_4__* p_rcb; int /*<<< orphan*/  bta_conn_id; void* is_full; int /*<<< orphan*/  p_cmd_list; TYPE_1__* p_srcb; } ;
typedef  TYPE_6__ tBTA_GATTC_CLCB ;
struct TYPE_14__ {void* is_full; int /*<<< orphan*/  conn_id; } ;
struct TYPE_18__ {TYPE_3__ queue_full; int /*<<< orphan*/  status; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ tBTA_GATTC ;
typedef  int /*<<< orphan*/  list_node_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_7__*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  server_bda; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_QUEUE_FULL_EVT ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 void* FALSE ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 scalar_t__ bta_gattc_sm_execute (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/ * l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ list_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static void bta_gattc_pop_command_to_send(tBTA_GATTC_CLCB *p_clcb)
{
    if (!list_is_empty(p_clcb->p_cmd_list)) {
        list_node_t *node = list_begin(p_clcb->p_cmd_list);
        tBTA_GATTC_DATA *p_data = (tBTA_GATTC_DATA *)list_node(node);
        if (p_data != NULL) {
            /* execute pending operation of link block still present */
            if (l2cu_find_lcb_by_bd_addr(p_clcb->p_srcb->server_bda, BT_TRANSPORT_LE) != NULL) {
                // The data to be sent to the gattc state machine for processing
                if(bta_gattc_sm_execute(p_clcb, p_data->hdr.event, p_data)) {
                    list_remove(p_clcb->p_cmd_list, (void *)p_data);
                }

                if (p_clcb->is_full) {
                    tBTA_GATTC cb_data = {0};
                    p_clcb->is_full = FALSE;
                    cb_data.status = GATT_SUCCESS;
                    cb_data.queue_full.conn_id = p_clcb->bta_conn_id;
                    cb_data.queue_full.is_full = FALSE;
                    if (p_clcb->p_rcb->p_cback != NULL) {
                        ( *p_clcb->p_rcb->p_cback)(BTA_GATTC_QUEUE_FULL_EVT, (tBTA_GATTC *)&cb_data);
                    }
                }
            }
        }
    }
}