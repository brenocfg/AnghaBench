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
struct hpsb_packet {int ack_code; scalar_t__ state; scalar_t__ sendtime; int /*<<< orphan*/  queue; int /*<<< orphan*/  expect_response; int /*<<< orphan*/  refcnt; scalar_t__ no_waiter; } ;
struct hpsb_host {scalar_t__ timeout_interval; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int ACK_PENDING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ hpsb_complete ; 
 int /*<<< orphan*/  hpsb_free_packet (struct hpsb_packet*) ; 
 scalar_t__ hpsb_pending ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pending_packets_lock ; 
 int /*<<< orphan*/  queue_packet_complete (struct hpsb_packet*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void hpsb_packet_sent(struct hpsb_host *host, struct hpsb_packet *packet,
		      int ackcode)
{
	unsigned long flags;

	spin_lock_irqsave(&pending_packets_lock, flags);

	packet->ack_code = ackcode;

	if (packet->no_waiter || packet->state == hpsb_complete) {
		/* if packet->no_waiter, must not have a tlabel allocated */
		spin_unlock_irqrestore(&pending_packets_lock, flags);
		hpsb_free_packet(packet);
		return;
	}

	atomic_dec(&packet->refcnt);	/* drop HC's reference */
	/* here the packet must be on the host->pending_packets queue */

	if (ackcode != ACK_PENDING || !packet->expect_response) {
		packet->state = hpsb_complete;
		list_del_init(&packet->queue);
		spin_unlock_irqrestore(&pending_packets_lock, flags);
		queue_packet_complete(packet);
		return;
	}

	packet->state = hpsb_pending;
	packet->sendtime = jiffies;

	spin_unlock_irqrestore(&pending_packets_lock, flags);

	mod_timer(&host->timeout, jiffies + host->timeout_interval);
}