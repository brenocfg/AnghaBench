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
struct hpsb_iso {int buf_packets; int n_ready_packets; int xmit_cycle; int pkt_dma; int /*<<< orphan*/  lock; int /*<<< orphan*/  overflows; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void hpsb_iso_packet_sent(struct hpsb_iso *iso, int cycle, int error)
{
	unsigned long flags;
	spin_lock_irqsave(&iso->lock, flags);

	/* predict the cycle of the next packet to be queued */

	/* jump ahead by the number of packets that are already buffered */
	cycle += iso->buf_packets - iso->n_ready_packets;
	cycle %= 8000;

	iso->xmit_cycle = cycle;
	iso->n_ready_packets++;
	iso->pkt_dma = (iso->pkt_dma + 1) % iso->buf_packets;

	if (iso->n_ready_packets == iso->buf_packets || error != 0) {
		/* the buffer has run empty! */
		atomic_inc(&iso->overflows);
	}

	spin_unlock_irqrestore(&iso->lock, flags);
}