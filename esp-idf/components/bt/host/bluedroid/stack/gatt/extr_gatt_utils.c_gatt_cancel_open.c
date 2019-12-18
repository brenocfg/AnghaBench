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
 scalar_t__ GATT_CH_OPEN ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gatt_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_get_ch_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_num_apps_hold_link (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_update_app_use_link_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN gatt_cancel_open(tGATT_IF gatt_if, BD_ADDR bda)
{
    tGATT_TCB *p_tcb = NULL;
    BOOLEAN status = TRUE;

    p_tcb = gatt_find_tcb_by_addr(bda, BT_TRANSPORT_LE);

    if (p_tcb) {
        if (gatt_get_ch_state(p_tcb) == GATT_CH_OPEN) {
            GATT_TRACE_ERROR("GATT_CancelConnect - link connected Too late to cancel");
            status = FALSE;
        } else {
            gatt_update_app_use_link_flag(gatt_if, p_tcb, FALSE, FALSE);
            if (!gatt_num_apps_hold_link(p_tcb)) {
                gatt_disconnect(p_tcb);
            }
        }
    }

    return status;
}