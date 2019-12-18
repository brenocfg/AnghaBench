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
struct pktcdvd_device {int dummy; } ;
struct packet_stacked_data {int /*<<< orphan*/  bio; struct pktcdvd_device* pd; } ;
struct bio {struct packet_stacked_data* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  mempool_free (struct packet_stacked_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_bio_finished (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  psd_pool ; 

__attribute__((used)) static void pkt_end_io_read_cloned(struct bio *bio, int err)
{
	struct packet_stacked_data *psd = bio->bi_private;
	struct pktcdvd_device *pd = psd->pd;

	bio_put(bio);
	bio_endio(psd->bio, err);
	mempool_free(psd, psd_pool);
	pkt_bio_finished(pd);
}