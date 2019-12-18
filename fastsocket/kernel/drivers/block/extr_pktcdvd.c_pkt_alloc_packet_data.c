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
struct packet_data {int frames; struct bio* w_bio; scalar_t__* pages; struct bio** r_bios; int /*<<< orphan*/  lock; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int FRAMES_PER_PAGE ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 scalar_t__ alloc_page (int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  kfree (struct packet_data*) ; 
 struct packet_data* kzalloc (int,int) ; 
 void* pkt_bio_alloc (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct packet_data *pkt_alloc_packet_data(int frames)
{
	int i;
	struct packet_data *pkt;

	pkt = kzalloc(sizeof(struct packet_data), GFP_KERNEL);
	if (!pkt)
		goto no_pkt;

	pkt->frames = frames;
	pkt->w_bio = pkt_bio_alloc(frames);
	if (!pkt->w_bio)
		goto no_bio;

	for (i = 0; i < frames / FRAMES_PER_PAGE; i++) {
		pkt->pages[i] = alloc_page(GFP_KERNEL|__GFP_ZERO);
		if (!pkt->pages[i])
			goto no_page;
	}

	spin_lock_init(&pkt->lock);

	for (i = 0; i < frames; i++) {
		struct bio *bio = pkt_bio_alloc(1);
		if (!bio)
			goto no_rd_bio;
		pkt->r_bios[i] = bio;
	}

	return pkt;

no_rd_bio:
	for (i = 0; i < frames; i++) {
		struct bio *bio = pkt->r_bios[i];
		if (bio)
			bio_put(bio);
	}

no_page:
	for (i = 0; i < frames / FRAMES_PER_PAGE; i++)
		if (pkt->pages[i])
			__free_page(pkt->pages[i]);
	bio_put(pkt->w_bio);
no_bio:
	kfree(pkt);
no_pkt:
	return NULL;
}