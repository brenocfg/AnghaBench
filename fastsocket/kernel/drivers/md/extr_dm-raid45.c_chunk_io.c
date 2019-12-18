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

/* Variables and functions */
 scalar_t__ ChunkDirty (struct stripe_chunk*) ; 
 int /*<<< orphan*/  ChunkIo (struct stripe_chunk*) ; 
 scalar_t__ ChunkLocked (struct stripe_chunk*) ; 
 int /*<<< orphan*/  ChunkUptodate (struct stripe_chunk*) ; 
 int /*<<< orphan*/  SetChunkMustIo (struct stripe_chunk*) ; 
 scalar_t__ TestClearChunkMustIo (struct stripe_chunk*) ; 

__attribute__((used)) static int chunk_io(struct stripe_chunk *chunk)
{
	/* 2nd run optimization (flag set below on first run). */
	if (TestClearChunkMustIo(chunk))
		return 1;

	/* Avoid io if prohibited or a locked chunk. */
	if (!ChunkIo(chunk) || ChunkLocked(chunk))
		return 0;

	if (!ChunkUptodate(chunk) || ChunkDirty(chunk)) {
		SetChunkMustIo(chunk); /* 2nd run optimization. */
		return 1;
	}

	return 0;
}