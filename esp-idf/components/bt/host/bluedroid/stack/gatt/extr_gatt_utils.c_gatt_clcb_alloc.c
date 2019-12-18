#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_REG ;
typedef  int /*<<< orphan*/  tGATT_IF ;
struct TYPE_4__ {size_t clcb_idx; int /*<<< orphan*/ * p_tcb; int /*<<< orphan*/ * p_reg; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ tGATT_CLCB ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_5__ {TYPE_1__* clcb; } ;

/* Variables and functions */
 size_t GATT_CL_MAX_LCB ; 
 int /*<<< orphan*/  GATT_GET_GATT_IF (int /*<<< orphan*/ ) ; 
 size_t GATT_GET_TCB_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ gatt_cb ; 
 int /*<<< orphan*/ * gatt_get_regcb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gatt_get_tcb_by_idx (size_t) ; 

tGATT_CLCB *gatt_clcb_alloc (UINT16 conn_id)
{
    UINT8           i = 0;
    tGATT_CLCB      *p_clcb = NULL;
    tGATT_IF        gatt_if = GATT_GET_GATT_IF(conn_id);
    UINT8           tcb_idx = GATT_GET_TCB_IDX(conn_id);
    tGATT_TCB       *p_tcb = gatt_get_tcb_by_idx(tcb_idx);
    tGATT_REG       *p_reg = gatt_get_regcb(gatt_if);

    for (i = 0; i < GATT_CL_MAX_LCB; i++) {
        if (!gatt_cb.clcb[i].in_use) {
            p_clcb = &gatt_cb.clcb[i];

            p_clcb->in_use      = TRUE;
            p_clcb->conn_id     = conn_id;
            p_clcb->clcb_idx    = i;
            p_clcb->p_reg       = p_reg;
            p_clcb->p_tcb       = p_tcb;
            break;
        }
    }
    return p_clcb;
}