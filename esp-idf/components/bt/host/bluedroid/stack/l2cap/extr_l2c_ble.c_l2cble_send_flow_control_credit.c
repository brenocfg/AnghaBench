#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* p_lcb; } ;
typedef  TYPE_2__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_5__ {scalar_t__ transport; } ;

/* Variables and functions */
 scalar_t__ BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  l2cu_send_peer_ble_flow_control_credit (TYPE_2__*,int /*<<< orphan*/ ) ; 

void l2cble_send_flow_control_credit(tL2C_CCB *p_ccb, UINT16 credit_value)
{
    if (!p_ccb) {
        return;
    }

    if (p_ccb->p_lcb && p_ccb->p_lcb->transport != BT_TRANSPORT_LE)
    {
        L2CAP_TRACE_WARNING ("LE link doesn't exist");
        return;
    }

    l2cu_send_peer_ble_flow_control_credit(p_ccb, credit_value);
    return;

}