#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * p_nocp_cb; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  tL2CA_NOCP_CB ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_RegForNoCPEvt(tL2CA_NOCP_CB *p_cb, BD_ADDR p_bda)
{
    tL2C_LCB        *p_lcb;

    /* Find the link that is associated with this remote bdaddr */
    p_lcb = l2cu_find_lcb_by_bd_addr (p_bda, BT_TRANSPORT_BR_EDR);

    /* If no link for this handle, nothing to do. */
    if (!p_lcb) {
        return FALSE;
    }

    p_lcb->p_nocp_cb = p_cb;

    return TRUE;
}