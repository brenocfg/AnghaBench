#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stripe_chunk {TYPE_1__* stripe; } ;
struct TYPE_5__ {scalar_t__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAN ; 
 int /*<<< orphan*/  ClearChunkLocked (struct stripe_chunk*) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_3__* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ S_STRIPE_ERROR ; 
 int /*<<< orphan*/  SetChunkUnlock (struct stripe_chunk*) ; 
 unsigned long StripeRecover (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int /*<<< orphan*/  chunk_set (struct stripe_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripe_put_references (TYPE_1__*) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static void endio(unsigned long error, void *context)
{
	struct stripe_chunk *chunk = context;

	if (unlikely(error)) {
		chunk_set(chunk, ERROR);
		/* REMOVEME: statistics. */
		atomic_inc(RS(chunk->stripe->sc)->stats + S_STRIPE_ERROR);
	} else
		chunk_set(chunk, CLEAN);

	/*
	 * For recovery stripes, I need to reset locked locked
	 * here, because those aren't processed in do_endios().
	 */
	if (unlikely(StripeRecover(chunk->stripe)))
		ClearChunkLocked(chunk);
	else
		SetChunkUnlock(chunk);

	/* Indirectly puts stripe on cache's endio list via stripe_io_put(). */
	stripe_put_references(chunk->stripe);
}