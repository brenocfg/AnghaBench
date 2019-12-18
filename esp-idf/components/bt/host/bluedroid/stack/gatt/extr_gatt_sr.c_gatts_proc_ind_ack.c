#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_2__ {scalar_t__ handle_of_h_r; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ gatt_cb ; 
 int /*<<< orphan*/  gatts_chk_pending_ind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatts_proc_srv_chg_ind_ack (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOLEAN gatts_proc_ind_ack(tGATT_TCB *p_tcb, UINT16 ack_handle)
{
    BOOLEAN continue_processing = TRUE;

    GATT_TRACE_DEBUG ("gatts_proc_ind_ack ack handle=%d", ack_handle);

    if (ack_handle == gatt_cb.handle_of_h_r) {
        gatts_proc_srv_chg_ind_ack(p_tcb);
        /* there is no need to inform the application since srv chg is handled internally by GATT */
        continue_processing = FALSE;
    }

    gatts_chk_pending_ind(p_tcb);
    return continue_processing;
}