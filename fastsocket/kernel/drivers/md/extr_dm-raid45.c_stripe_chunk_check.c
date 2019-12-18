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
struct stripe_chunk {int dummy; } ;
struct stripe {int /*<<< orphan*/  sc; } ;
struct raid_set {unsigned int dev; scalar_t__ stats; } ;

/* Variables and functions */
 struct stripe_chunk* CHUNK (struct stripe*,unsigned int) ; 
 scalar_t__ ChunkError (struct stripe_chunk*) ; 
 scalar_t__ ChunkLocked (struct stripe_chunk*) ; 
 scalar_t__ ChunkUptodate (struct stripe_chunk*) ; 
 scalar_t__ DevFailed (unsigned int) ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ S_CHUNK_LOCKED ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 

__attribute__((used)) static struct stripe_chunk *
stripe_chunk_check(struct stripe *stripe, unsigned p, unsigned *chunks_uptodate)
{
	struct raid_set *rs = RS(stripe->sc);
	struct stripe_chunk *chunk = CHUNK(stripe, p);

	/* Can't access active chunks. */
	if (ChunkLocked(chunk)) {
		/* REMOVEME: statistics. */
		atomic_inc(rs->stats + S_CHUNK_LOCKED);
		return NULL;
	}

	/* Can't access broken devive. */
	if (ChunkError(chunk) || DevFailed(rs->dev + p))
		return NULL;

	/* Can access uptodate chunks. */
	if (ChunkUptodate(chunk)) {
		(*chunks_uptodate)++;
		return NULL;
	}

	return chunk;
}