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
struct stripe_chunk {int /*<<< orphan*/  stripe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_CHUNK (struct stripe_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ ChunkUptodate (struct stripe_chunk*) ; 
 scalar_t__ StripeReconstruct (int /*<<< orphan*/ ) ; 
 scalar_t__ StripeRecover (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_MERGED ; 
 int /*<<< orphan*/  WRITE_QUEUED ; 
 int /*<<< orphan*/  bio_list_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int chunk_must_xor(struct stripe_chunk *chunk)
{
	if (ChunkUptodate(chunk)) {
		BUG_ON(!bio_list_empty(BL_CHUNK(chunk, WRITE_QUEUED)) &&
		       !bio_list_empty(BL_CHUNK(chunk, WRITE_MERGED)));

		if (!bio_list_empty(BL_CHUNK(chunk, WRITE_QUEUED)) ||
		    !bio_list_empty(BL_CHUNK(chunk, WRITE_MERGED)))
			return 1;

		if (StripeReconstruct(chunk->stripe) ||
		    StripeRecover(chunk->stripe))
			return 1;
	}

	return 0;
}