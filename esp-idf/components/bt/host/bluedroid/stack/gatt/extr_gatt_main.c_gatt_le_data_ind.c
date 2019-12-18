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
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 scalar_t__ GATT_CH_OPEN ; 
 int /*<<< orphan*/  GATT_TRACE_WARNING (char*,scalar_t__) ; 
 int /*<<< orphan*/  gatt_data_process (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_get_ch_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gatt_le_data_ind (UINT16 chan, BD_ADDR bd_addr, BT_HDR *p_buf)
{
    tGATT_TCB    *p_tcb;

    /* Find CCB based on bd addr */
    if ((p_tcb = gatt_find_tcb_by_addr (bd_addr, BT_TRANSPORT_LE)) != NULL &&
            gatt_get_ch_state(p_tcb) >= GATT_CH_OPEN) {
        gatt_data_process(p_tcb, p_buf);
    } else {
        osi_free (p_buf);

        if (p_tcb != NULL) {
            GATT_TRACE_WARNING ("ATT - Ignored L2CAP data while in state: %d\n",
                                gatt_get_ch_state(p_tcb));
        }
    }
}