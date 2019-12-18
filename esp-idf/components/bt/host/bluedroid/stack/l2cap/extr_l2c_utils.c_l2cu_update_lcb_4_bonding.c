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
struct TYPE_3__ {int /*<<< orphan*/  is_bonding; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void l2cu_update_lcb_4_bonding (BD_ADDR p_bd_addr, BOOLEAN is_bonding)
{
    tL2C_LCB    *p_lcb = l2cu_find_lcb_by_bd_addr (p_bd_addr, BT_TRANSPORT_BR_EDR);

    if (p_lcb) {
        p_lcb->is_bonding = is_bonding;
    }
}