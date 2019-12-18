#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ operation; int /*<<< orphan*/  counter; TYPE_2__* p_tcb; } ;
typedef  TYPE_1__ tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_8__ {int /*<<< orphan*/  pending_enc_clcb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ GATTC_OPTYPE_READ ; 
 scalar_t__ GATTC_OPTYPE_WRITE ; 
 int /*<<< orphan*/  GATT_AUTH_FAIL ; 
 int /*<<< orphan*/  GATT_SEC_NONE ; 
 scalar_t__ fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_act_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_act_write (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_end_operation (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_set_sec_act (TYPE_2__*,int /*<<< orphan*/ ) ; 

void gatt_sec_check_complete(BOOLEAN sec_check_ok, tGATT_CLCB   *p_clcb, UINT8 sec_act)
{
    if (p_clcb && p_clcb->p_tcb &&
        fixed_queue_is_empty(p_clcb->p_tcb->pending_enc_clcb)) {
        gatt_set_sec_act(p_clcb->p_tcb, GATT_SEC_NONE);
    }
#if (GATTC_INCLUDED == TRUE)
    if (!sec_check_ok) {
        gatt_end_operation(p_clcb, GATT_AUTH_FAIL, NULL);
    } else if (p_clcb->operation == GATTC_OPTYPE_WRITE) {
        gatt_act_write(p_clcb, sec_act);
    } else if (p_clcb->operation == GATTC_OPTYPE_READ) {
        gatt_act_read(p_clcb, p_clcb->counter);
    }
#endif  ///GATTC_INCLUDED == TRUE
}