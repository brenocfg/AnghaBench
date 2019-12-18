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
typedef  enum chunk_dirty_type { ____Placeholder_chunk_dirty_type } chunk_dirty_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLEAN 130 
 int /*<<< orphan*/  ClearChunkDirty (struct stripe_chunk*) ; 
 int /*<<< orphan*/  ClearChunkError (struct stripe_chunk*) ; 
#define  DIRTY 129 
#define  ERROR 128 
 int /*<<< orphan*/  SetChunkDirty (struct stripe_chunk*) ; 
 int /*<<< orphan*/  SetChunkError (struct stripe_chunk*) ; 
 int /*<<< orphan*/  SetChunkIo (struct stripe_chunk*) ; 
 int /*<<< orphan*/  SetChunkUptodate (struct stripe_chunk*) ; 
 int /*<<< orphan*/  SetStripeError (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chunk_set(struct stripe_chunk *chunk, enum chunk_dirty_type type)
{
	switch (type) {
	case CLEAN:
		ClearChunkDirty(chunk);
		break;
	case DIRTY:
		SetChunkDirty(chunk);
		break;
	case ERROR:
		SetChunkError(chunk);
		SetStripeError(chunk->stripe);
		return;
	default:
		BUG();
	}

	SetChunkUptodate(chunk);
	SetChunkIo(chunk);
	ClearChunkError(chunk);
}