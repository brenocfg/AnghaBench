#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_NO_RESOURCES ; 
 int /*<<< orphan*/  L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  attp_send_msg_to_l2cap (int /*<<< orphan*/ *,TYPE_1__*) ; 

tGATT_STATUS attp_send_sr_msg (tGATT_TCB *p_tcb, BT_HDR *p_msg)
{
    tGATT_STATUS     cmd_sent = GATT_NO_RESOURCES;

    if (p_tcb != NULL) {
        if (p_msg != NULL) {
            p_msg->offset = L2CAP_MIN_OFFSET;
            cmd_sent = attp_send_msg_to_l2cap (p_tcb, p_msg);
        }
    }
    return cmd_sent;
}