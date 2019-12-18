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
struct TYPE_3__ {int /*<<< orphan*/  link_role; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  HCI_ROLE_UNKNOWN ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT8 L2CA_GetBleConnRole (BD_ADDR bd_addr)
{
    UINT8       role = HCI_ROLE_UNKNOWN;

    tL2C_LCB *p_lcb;

    if ((p_lcb = l2cu_find_lcb_by_bd_addr (bd_addr, BT_TRANSPORT_LE)) != NULL) {
        role = p_lcb->link_role;
    }

    return role;
}