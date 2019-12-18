#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ tGATT_STATUS ;
struct TYPE_19__ {scalar_t__ uuid16; } ;
struct TYPE_20__ {int len; TYPE_4__ uu; } ;
struct TYPE_21__ {scalar_t__ s_handle; scalar_t__ e_handle; int /*<<< orphan*/  value; int /*<<< orphan*/  value_len; TYPE_5__ uuid; } ;
struct TYPE_16__ {scalar_t__ uuid16; } ;
struct TYPE_17__ {int len; TYPE_1__ uu; } ;
struct TYPE_18__ {scalar_t__ s_handle; scalar_t__ e_handle; TYPE_2__ uuid; } ;
struct TYPE_23__ {TYPE_6__ find_type_value; TYPE_3__ browse; } ;
typedef  TYPE_8__ tGATT_CL_MSG ;
struct TYPE_15__ {int /*<<< orphan*/  uuid32; } ;
struct TYPE_22__ {int /*<<< orphan*/  len; TYPE_11__ uu; } ;
struct TYPE_24__ {size_t op_subtype; scalar_t__ s_handle; scalar_t__ e_handle; int /*<<< orphan*/  clcb_idx; int /*<<< orphan*/  p_tcb; TYPE_7__ uuid; } ;
typedef  TYPE_9__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 scalar_t__ GATT_CMD_STARTED ; 
 size_t GATT_DISC_SRVC_BY_UUID ; 
 scalar_t__ GATT_ERROR ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  LEN_UUID_128 ; 
 int /*<<< orphan*/  LEN_UUID_32 ; 
 scalar_t__ attp_send_cl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/ * disc_type_to_att_opcode ; 
 scalar_t__* disc_type_to_uuid ; 
 int /*<<< orphan*/  gatt_convert_uuid32_to_uuid128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_9__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

void gatt_act_discovery(tGATT_CLCB *p_clcb)
{
    UINT8       op_code = disc_type_to_att_opcode[p_clcb->op_subtype];
    tGATT_CL_MSG   cl_req;
    tGATT_STATUS    st;

    if (p_clcb->s_handle <= p_clcb->e_handle && p_clcb->s_handle != 0) {
        memset(&cl_req, 0, sizeof(tGATT_CL_MSG));

        cl_req.browse.s_handle = p_clcb->s_handle;
        cl_req.browse.e_handle = p_clcb->e_handle;

        if (disc_type_to_uuid[p_clcb->op_subtype] != 0) {
            cl_req.browse.uuid.len = 2;
            cl_req.browse.uuid.uu.uuid16 = disc_type_to_uuid[p_clcb->op_subtype];
        }

        if (p_clcb->op_subtype == GATT_DISC_SRVC_BY_UUID) { /* fill in the FindByTypeValue request info*/
            cl_req.find_type_value.uuid.len = 2;
            cl_req.find_type_value.uuid.uu.uuid16 = disc_type_to_uuid[p_clcb->op_subtype];
            cl_req.find_type_value.s_handle = p_clcb->s_handle;
            cl_req.find_type_value.e_handle = p_clcb->e_handle;
            cl_req.find_type_value.value_len = p_clcb->uuid.len;
            /* if service type is 32 bits UUID, convert it now */
            if (p_clcb->uuid.len == LEN_UUID_32) {
                cl_req.find_type_value.value_len = LEN_UUID_128;
                gatt_convert_uuid32_to_uuid128(cl_req.find_type_value.value, p_clcb->uuid.uu.uuid32);
            } else {
                memcpy (cl_req.find_type_value.value,  &p_clcb->uuid.uu, p_clcb->uuid.len);
            }
        }

        st = attp_send_cl_msg(p_clcb->p_tcb, p_clcb->clcb_idx, op_code, &cl_req);

        if (st !=  GATT_SUCCESS && st != GATT_CMD_STARTED) {
            gatt_end_operation(p_clcb, GATT_ERROR, NULL);
        }
    } else { /* end of handle range */
        gatt_end_operation(p_clcb, GATT_SUCCESS, NULL);
    }
}