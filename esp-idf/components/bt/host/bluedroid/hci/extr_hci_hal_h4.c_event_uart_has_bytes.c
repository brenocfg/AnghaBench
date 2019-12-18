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
typedef  int /*<<< orphan*/  fixed_queue_t ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/ * fixed_queue_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_hal_h4_hdl_rx_packet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void event_uart_has_bytes(fixed_queue_t *queue)
{
    BT_HDR *packet;
    while (!fixed_queue_is_empty(queue)) {
        packet = fixed_queue_dequeue(queue, FIXED_QUEUE_MAX_TIMEOUT);
        hci_hal_h4_hdl_rx_packet(packet);
    }
}