#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* transmit_downward ) (scalar_t__,TYPE_1__*) ;} ;
struct TYPE_6__ {scalar_t__ event; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 scalar_t__ BT_SUB_EVT_MASK ; 
 scalar_t__ LOCAL_BLE_CONTROLLER_ID ; 
 scalar_t__ LOCAL_BR_EDR_CONTROLLER_ID ; 
 TYPE_4__* hci ; 
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,TYPE_1__*) ; 

void bte_main_hci_send (BT_HDR *p_msg, UINT16 event)
{
    UINT16 sub_event = event & BT_SUB_EVT_MASK;  /* local controller ID */

    p_msg->event = event;

    //counter_add("main.tx.packets", 1);
    //counter_add("main.tx.bytes", p_msg->len);

    if ((sub_event == LOCAL_BR_EDR_CONTROLLER_ID) || \
            (sub_event == LOCAL_BLE_CONTROLLER_ID)) {
        hci->transmit_downward(event, p_msg);
    } else {
        //APPL_TRACE_ERROR("Invalid Controller ID. Discarding message.");
        osi_free(p_msg);
    }
}