#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_IF ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_update_app_use_link_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_update_auto_connect_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN gatt_remove_bg_dev_for_app(tGATT_IF gatt_if, BD_ADDR bd_addr)
{
    tGATT_TCB    *p_tcb = gatt_find_tcb_by_addr(bd_addr, BT_TRANSPORT_LE);
    BOOLEAN       status;

    if (p_tcb) {
        gatt_update_app_use_link_flag(gatt_if, p_tcb, FALSE, FALSE);
    }
    status = gatt_update_auto_connect_dev(gatt_if, FALSE, bd_addr, TRUE);
    return status;
}