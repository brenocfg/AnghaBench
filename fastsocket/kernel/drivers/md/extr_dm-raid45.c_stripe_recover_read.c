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
struct stripe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHUNK (struct stripe*,int) ; 
 int /*<<< orphan*/  ClearChunkIo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_allow_io (struct stripe*) ; 
 int /*<<< orphan*/  stripe_chunks_invalidate (struct stripe*) ; 
 int stripe_chunks_rw (struct stripe*) ; 
 int /*<<< orphan*/  stripe_io_ref (struct stripe*) ; 

__attribute__((used)) static int stripe_recover_read(struct stripe *stripe, int pi)
{
	BUG_ON(stripe_io_ref(stripe));

	/* Invalidate all chunks so that they get read in. */
	stripe_chunks_invalidate(stripe);
	stripe_allow_io(stripe); /* Allow io on all recovery chunks. */

	/*
	 * If we are reconstructing a perticular device, we can avoid
	 * reading the respective chunk in, because we're going to
	 * reconstruct it anyway.
	 *
	 * We can't do that for resynchronization of rotating parity,
	 * because the recovery stripe chunk size is typically larger
	 * than the sets chunk size.
	 */
	if (pi > -1)
		ClearChunkIo(CHUNK(stripe, pi));

	return stripe_chunks_rw(stripe);
}