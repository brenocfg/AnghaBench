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
typedef  int /*<<< orphan*/  tGATT_REG ;
typedef  int /*<<< orphan*/  tGATT_IF ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GATT_TRACE_API (char*) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gatt_add_bg_dev_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gatt_get_regcb (int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_remove_bg_dev_from_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gatt_update_app_use_link_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN gatt_update_auto_connect_dev (tGATT_IF gatt_if, BOOLEAN add, BD_ADDR bd_addr, BOOLEAN is_initator)
{
    BOOLEAN         ret = FALSE;
    tGATT_REG        *p_reg;
    tGATT_TCB       *p_tcb = gatt_find_tcb_by_addr(bd_addr, BT_TRANSPORT_LE);

    GATT_TRACE_API ("gatt_update_auto_connect_dev ");
    /* Make sure app is registered */
    if ((p_reg = gatt_get_regcb(gatt_if)) == NULL) {
        GATT_TRACE_ERROR("gatt_update_auto_connect_dev - gatt_if %d is not registered", gatt_if);
        return (FALSE);
    }

    if (add) {
        ret = gatt_add_bg_dev_list(p_reg, bd_addr, is_initator);

        if (ret && p_tcb != NULL) {
            /* if a connected device, update the link holding number */
            gatt_update_app_use_link_flag(gatt_if, p_tcb, TRUE, TRUE);
        }
    } else {
        ret = gatt_remove_bg_dev_from_list(p_reg, bd_addr, is_initator);
    }
    return ret;
}