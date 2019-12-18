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
struct stripe_chunk {struct bio_list* bl; } ;
struct stripe {int /*<<< orphan*/  sc; } ;
struct TYPE_2__ {unsigned int raid_devs; } ;
struct raid_set {TYPE_1__ set; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bio_list*) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct stripe_chunk* CHUNK (struct stripe*,unsigned int) ; 
 int /*<<< orphan*/  EIO ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_empty (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_endio (struct stripe*,struct bio_list*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_io_ref (struct stripe*) ; 
 int /*<<< orphan*/  stripe_ref (struct stripe*) ; 

__attribute__((used)) static void stripe_fail_io(struct stripe *stripe)
{
	struct raid_set *rs = RS(stripe->sc);
	unsigned p = rs->set.raid_devs;

	while (p--) {
		struct stripe_chunk *chunk = CHUNK(stripe, p);
		int i = ARRAY_SIZE(chunk->bl);

		/* Fail all bios on all bio lists of the stripe. */
		while (i--) {
			struct bio_list *bl = chunk->bl + i;

			if (!bio_list_empty(bl))
				bio_list_endio(stripe, bl, p, -EIO);
		}
	}

	/* Put stripe on LRU list. */
	BUG_ON(stripe_io_ref(stripe));
	BUG_ON(stripe_ref(stripe));
}