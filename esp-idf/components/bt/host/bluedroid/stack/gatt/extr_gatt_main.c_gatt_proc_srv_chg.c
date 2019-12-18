#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  size_t UINT8 ;
struct TYPE_3__ {scalar_t__ p_srv_chg_callback; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tcb; scalar_t__ handle_of_h_r; TYPE_1__ cb_info; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 TYPE_2__ gatt_cb ; 
 scalar_t__ gatt_find_the_connected_bda (size_t,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_is_srv_chg_ind_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gatt_send_srv_chg_ind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_set_srv_chg () ; 

void gatt_proc_srv_chg (void)
{
    UINT8               start_idx, found_idx;
    BD_ADDR             bda;
    BOOLEAN             srv_chg_ind_pending = FALSE;
    tGATT_TCB           *p_tcb;
    tBT_TRANSPORT      transport;

    GATT_TRACE_DEBUG ("gatt_proc_srv_chg");

    if (gatt_cb.cb_info.p_srv_chg_callback && gatt_cb.handle_of_h_r) {
        gatt_set_srv_chg();
        start_idx = 0;
        while (gatt_find_the_connected_bda(start_idx, bda, &found_idx, &transport)) {
            p_tcb = &gatt_cb.tcb[found_idx];
            srv_chg_ind_pending  = gatt_is_srv_chg_ind_pending(p_tcb);

            if (!srv_chg_ind_pending) {
                gatt_send_srv_chg_ind(bda);
            } else {
                GATT_TRACE_DEBUG ("discard srv chg - already has one in the queue");
            }
            start_idx = ++found_idx;
        }
    }
}