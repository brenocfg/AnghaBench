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
struct TYPE_2__ {int /*<<< orphan*/  pkt_ended; } ;
struct pktcdvd_device {int /*<<< orphan*/  wqueue; TYPE_1__ stats; } ;
struct packet_data {int /*<<< orphan*/  run_sm; int /*<<< orphan*/  io_wait; int /*<<< orphan*/  id; struct pktcdvd_device* pd; } ;
struct bio {struct packet_data* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  VPRINTK (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_bio_finished (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_end_io_packet_write(struct bio *bio, int err)
{
	struct packet_data *pkt = bio->bi_private;
	struct pktcdvd_device *pd = pkt->pd;
	BUG_ON(!pd);

	VPRINTK("pkt_end_io_packet_write: id=%d, err=%d\n", pkt->id, err);

	pd->stats.pkt_ended++;

	pkt_bio_finished(pd);
	atomic_dec(&pkt->io_wait);
	atomic_inc(&pkt->run_sm);
	wake_up(&pd->wqueue);
}