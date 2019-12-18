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
struct hpsb_packet {int /*<<< orphan*/  queue; int /*<<< orphan*/ * complete_routine; scalar_t__ no_waiter; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpsb_free_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  hpsbpkt_queue ; 
 int /*<<< orphan*/  khpsbpkt_thread ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending_packets_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void queue_packet_complete(struct hpsb_packet *packet)
{
	unsigned long flags;

	if (packet->no_waiter) {
		hpsb_free_packet(packet);
		return;
	}
	if (packet->complete_routine != NULL) {
		spin_lock_irqsave(&pending_packets_lock, flags);
		list_add_tail(&packet->queue, &hpsbpkt_queue);
		spin_unlock_irqrestore(&pending_packets_lock, flags);
		wake_up_process(khpsbpkt_thread);
	}
	return;
}