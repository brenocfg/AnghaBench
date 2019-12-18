#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_first_ccb; } ;
struct TYPE_5__ {int /*<<< orphan*/  timer_entry; TYPE_1__ ccb_queue; } ;
typedef  TYPE_2__ tL2C_LCB ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_LINK ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  L2CAP_LINK_CONNECT_TOUT_EXT ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void l2c_pin_code_request (BD_ADDR bd_addr)
{
    tL2C_LCB *p_lcb = l2cu_find_lcb_by_bd_addr (bd_addr, BT_TRANSPORT_BR_EDR);

    if ( (p_lcb) && (!p_lcb->ccb_queue.p_first_ccb) ) {
        btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_CONNECT_TOUT_EXT);
    }
}