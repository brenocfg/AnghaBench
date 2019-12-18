#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
struct TYPE_17__ {scalar_t__ e_handle; int /*<<< orphan*/  service_type; } ;
struct TYPE_18__ {TYPE_5__ group_value; } ;
struct TYPE_13__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_14__ {int len; TYPE_1__ uu; } ;
struct TYPE_19__ {scalar_t__ handle; TYPE_6__ value; TYPE_2__ type; } ;
typedef  TYPE_7__ tGATT_DISC_RES ;
struct TYPE_20__ {scalar_t__ operation; scalar_t__ op_subtype; scalar_t__ s_handle; int /*<<< orphan*/  conn_id; TYPE_4__* p_reg; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_8__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  tBT_UUID ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_15__ {int /*<<< orphan*/  (* p_disc_res_cb ) (int /*<<< orphan*/ ,scalar_t__,TYPE_7__*) ;} ;
struct TYPE_16__ {TYPE_3__ app_cb; } ;

/* Variables and functions */
 scalar_t__ GATTC_OPTYPE_DISCOVERY ; 
 scalar_t__ GATT_DISC_SRVC_BY_UUID ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  GATT_UUID_PRI_SERVICE ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_act_discovery (TYPE_8__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,TYPE_7__*) ; 

void gatt_process_find_type_value_rsp (tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, UINT16 len, UINT8 *p_data)
{
    tGATT_DISC_RES      result;
    UINT8               *p = p_data;

    UNUSED(p_tcb);

    GATT_TRACE_DEBUG("gatt_process_find_type_value_rsp ");
    /* unexpected response */
    if (p_clcb->operation != GATTC_OPTYPE_DISCOVERY || p_clcb->op_subtype != GATT_DISC_SRVC_BY_UUID) {
        return;
    }

    memset (&result, 0, sizeof(tGATT_DISC_RES));
    result.type.len = 2;
    result.type.uu.uuid16 = GATT_UUID_PRI_SERVICE;

    /* returns a series of handle ranges */
    while (len >= 4) {
        STREAM_TO_UINT16 (result.handle, p);
        STREAM_TO_UINT16 (result.value.group_value.e_handle, p);
        memcpy (&result.value.group_value.service_type,  &p_clcb->uuid, sizeof(tBT_UUID));

        len -= 4;

        if (p_clcb->p_reg->app_cb.p_disc_res_cb) {
            (*p_clcb->p_reg->app_cb.p_disc_res_cb)(p_clcb->conn_id, p_clcb->op_subtype, &result);
        }
    }

    /* last handle  + 1 */
    p_clcb->s_handle = (result.value.group_value.e_handle == 0) ? 0 : (result.value.group_value.e_handle + 1);
    /* initiate another request */
    gatt_act_discovery(p_clcb) ;
}