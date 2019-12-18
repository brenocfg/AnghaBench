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
struct pktcdvd_device {int /*<<< orphan*/  wqueue; } ;
struct packet_data {int /*<<< orphan*/  run_sm; int /*<<< orphan*/  io_wait; int /*<<< orphan*/  io_errors; scalar_t__ sector; struct pktcdvd_device* pd; } ;
struct bio {scalar_t__ bi_sector; struct packet_data* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  VPRINTK (char*,struct bio*,unsigned long long,unsigned long long,int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_bio_finished (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_end_io_read(struct bio *bio, int err)
{
	struct packet_data *pkt = bio->bi_private;
	struct pktcdvd_device *pd = pkt->pd;
	BUG_ON(!pd);

	VPRINTK("pkt_end_io_read: bio=%p sec0=%llx sec=%llx err=%d\n", bio,
		(unsigned long long)pkt->sector, (unsigned long long)bio->bi_sector, err);

	if (err)
		atomic_inc(&pkt->io_errors);
	if (atomic_dec_and_test(&pkt->io_wait)) {
		atomic_inc(&pkt->run_sm);
		wake_up(&pd->wqueue);
	}
	pkt_bio_finished(pd);
}