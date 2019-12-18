#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_CL_COMPLETE ;
typedef  int /*<<< orphan*/  tGATTC_OPTYPE ;
typedef  int /*<<< orphan*/  tBTA_GATT_STATUS ;
struct TYPE_5__ {int layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p_cmpl; int /*<<< orphan*/  op_code; int /*<<< orphan*/  status; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_GATTC_OP_CMPL ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_OP_CMPL_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ osi_malloc (int const) ; 

__attribute__((used)) static void bta_gattc_cmpl_sendmsg(UINT16 conn_id, tGATTC_OPTYPE op,
                                   tBTA_GATT_STATUS status,
                                   tGATT_CL_COMPLETE *p_data)
{
    const UINT16         len = sizeof(tBTA_GATTC_OP_CMPL) + sizeof(tGATT_CL_COMPLETE);
    tBTA_GATTC_OP_CMPL  *p_buf = (tBTA_GATTC_OP_CMPL *) osi_malloc(len);

    if (p_buf != NULL) {
        memset(p_buf, 0, len);
        p_buf->hdr.event = BTA_GATTC_OP_CMPL_EVT;
        p_buf->hdr.layer_specific = conn_id;
        p_buf->status = status;
        p_buf->op_code = op;

        if (p_data != NULL) {
            p_buf->p_cmpl = (tGATT_CL_COMPLETE *)(p_buf + 1);
            memcpy(p_buf->p_cmpl, p_data, sizeof(tGATT_CL_COMPLETE));
        }

        bta_sys_sendmsg(p_buf);
    }
}