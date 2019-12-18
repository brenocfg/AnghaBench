#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t tcb_idx; int /*<<< orphan*/  peer_bda; int /*<<< orphan*/  transport; void* in_use; void* pending_ind_q; void* pending_enc_clcb; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  size_t UINT8 ;
struct TYPE_6__ {TYPE_1__* tcb; } ;
typedef  void* BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 void* FALSE ; 
 size_t GATT_INDEX_INVALID ; 
 int /*<<< orphan*/  QUEUE_SIZE_MAX ; 
 void* TRUE ; 
 void* fixed_queue_new (int /*<<< orphan*/ ) ; 
 TYPE_3__ gatt_cb ; 
 size_t gatt_find_i_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t gatt_find_i_tcb_free () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

tGATT_TCB *gatt_allocate_tcb_by_bdaddr(BD_ADDR bda, tBT_TRANSPORT transport)
{
    UINT8 i = 0;
    BOOLEAN allocated = FALSE;
    tGATT_TCB    *p_tcb = NULL;

    /* search for existing tcb with matching bda    */
    i = gatt_find_i_tcb_by_addr(bda, transport);
    /* find free tcb */
    if (i == GATT_INDEX_INVALID) {
        i = gatt_find_i_tcb_free();
        allocated = TRUE;
    }
    if (i != GATT_INDEX_INVALID) {
        p_tcb = &gatt_cb.tcb[i];

        if (allocated) {
            memset(p_tcb, 0, sizeof(tGATT_TCB));
            p_tcb->pending_enc_clcb = fixed_queue_new(QUEUE_SIZE_MAX);
            p_tcb->pending_ind_q = fixed_queue_new(QUEUE_SIZE_MAX);
            p_tcb->in_use = TRUE;
            p_tcb->tcb_idx = i;
            p_tcb->transport = transport;
        }
        memcpy(p_tcb->peer_bda, bda, BD_ADDR_LEN);
    }
    return p_tcb;
}