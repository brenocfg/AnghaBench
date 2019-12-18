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
struct packet_data {int /*<<< orphan*/ * orig_bios_tail; struct bio* orig_bios; scalar_t__ cache_valid; } ;
struct bio {struct bio* bi_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pkt_finish_packet(struct packet_data *pkt, int uptodate)
{
	struct bio *bio, *next;

	if (!uptodate)
		pkt->cache_valid = 0;

	/* Finish all bios corresponding to this packet */
	bio = pkt->orig_bios;
	while (bio) {
		next = bio->bi_next;
		bio->bi_next = NULL;
		bio_endio(bio, uptodate ? 0 : -EIO);
		bio = next;
	}
	pkt->orig_bios = pkt->orig_bios_tail = NULL;
}