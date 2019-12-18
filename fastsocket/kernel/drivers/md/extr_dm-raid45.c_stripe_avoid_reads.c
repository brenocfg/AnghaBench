#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stripe_chunk {int dummy; } ;
struct TYPE_4__ {unsigned int parity; } ;
struct stripe {int /*<<< orphan*/  sc; TYPE_2__ idx; } ;
struct TYPE_3__ {unsigned int raid_devs; } ;
struct raid_set {scalar_t__ stats; TYPE_1__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearChunkIo (struct stripe_chunk*) ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ S_PROHIBITCHUNKIO ; 
 int /*<<< orphan*/  SetChunkIo (struct stripe_chunk*) ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 scalar_t__ chunk_ref (struct stripe_chunk*) ; 
 struct stripe_chunk* stripe_chunk_check (struct stripe*,unsigned int,unsigned int*) ; 

__attribute__((used)) static void stripe_avoid_reads(struct stripe *stripe)
{
	struct raid_set *rs = RS(stripe->sc);
	unsigned dummy = 0, p = rs->set.raid_devs;

	/* Walk all chunks. */
	while (p--) {
		struct stripe_chunk *chunk =
			stripe_chunk_check(stripe, p, &dummy);

		if (!chunk)
			continue;

		/* If parity or any bios pending -> allow io. */
		if (chunk_ref(chunk) || p == stripe->idx.parity)
			SetChunkIo(chunk);
		else {
			ClearChunkIo(chunk);
			/* REMOVEME: statistics. */
			atomic_inc(RS(stripe->sc)->stats + S_PROHIBITCHUNKIO);
		}
	}
}