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
struct TYPE_4__ {scalar_t__ command_credits; int /*<<< orphan*/  packet_queue; int /*<<< orphan*/  command_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fragment_and_dispatch ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* fragment_current_packet ) () ;} ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 scalar_t__ esp_vhci_host_check_send_available () ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_process (int /*<<< orphan*/ ) ; 
 TYPE_2__ hci_host_env ; 
 TYPE_1__* packet_fragmenter ; 
 int /*<<< orphan*/ * stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_host_thread_handler(void *arg)
{
    /*
     * Previous task handles RX queue and two TX Queues, Since there is
     * a RX Thread Task in H4 layer which receives packet from driver layer.
     * Now HCI Host Task has been optimized to only process TX Queue
     * including command and data queue. And command queue has high priority,
     * All packets will be directly copied to single queue in driver layer with
     * H4 type header added (1 byte).
     */
    if (esp_vhci_host_check_send_available()) {
        /*Now Target only allowed one packet per TX*/
        BT_HDR *pkt = packet_fragmenter->fragment_current_packet();
        if (pkt != NULL) {
            packet_fragmenter->fragment_and_dispatch(pkt);
        } else {
            if (!fixed_queue_is_empty(hci_host_env.command_queue) &&
                    hci_host_env.command_credits > 0) {
                fixed_queue_process(hci_host_env.command_queue);
            } else if (!fixed_queue_is_empty(hci_host_env.packet_queue)) {
                fixed_queue_process(hci_host_env.packet_queue);
            }
        }
    }
}