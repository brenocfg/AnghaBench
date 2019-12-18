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
struct TYPE_2__ {scalar_t__ adv_free_num; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  btsnd_hcic_ble_update_adv_report_flow_control (scalar_t__) ; 
 scalar_t__ esp_vhci_host_check_send_available () ; 
 TYPE_1__ hci_hal_env ; 
 scalar_t__ host_recv_adv_packet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_update_adv_report_flow_control(BT_HDR *packet)
{
    // this is adv packet
    if(host_recv_adv_packet(packet)) {
        // update adv free number
        hci_hal_env.adv_free_num ++;
        if (esp_vhci_host_check_send_available()){
            // send hci cmd
            btsnd_hcic_ble_update_adv_report_flow_control(hci_hal_env.adv_free_num);
            hci_hal_env.adv_free_num = 0;
        } else {
            //do nothing
        }
    }

}