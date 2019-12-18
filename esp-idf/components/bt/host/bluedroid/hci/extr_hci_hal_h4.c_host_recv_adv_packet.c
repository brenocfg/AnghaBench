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
struct TYPE_4__ {scalar_t__* data; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_EVENT ; 
 scalar_t__ HCI_BLE_ADV_DISCARD_REPORT_EVT ; 
 scalar_t__ HCI_BLE_ADV_PKT_RPT_EVT ; 
 scalar_t__ HCI_BLE_EVENT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

bool host_recv_adv_packet(BT_HDR *packet)
{
    assert(packet);
    if(packet->data[0] == DATA_TYPE_EVENT && packet->data[1] == HCI_BLE_EVENT) {
        if(packet->data[3] ==  HCI_BLE_ADV_PKT_RPT_EVT 
#if (BLE_ADV_REPORT_FLOW_CONTROL == TRUE)
        || packet->data[3] ==  HCI_BLE_ADV_DISCARD_REPORT_EVT
#endif
        ) {
            return true;
        }
    }
    return false;
}