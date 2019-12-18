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
struct dm_snapshot {scalar_t__ first_merging_chunk; scalar_t__ num_merging_chunks; int /*<<< orphan*/  lock; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ chunk_t ;

/* Variables and functions */
 struct bio* __release_queued_bios_after_merge (struct dm_snapshot*) ; 
 int __remove_single_exception_chunk (struct dm_snapshot*,scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_bios (struct bio*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int remove_single_exception_chunk(struct dm_snapshot *s)
{
	struct bio *b = NULL;
	int r;
	chunk_t old_chunk = s->first_merging_chunk + s->num_merging_chunks - 1;

	down_write(&s->lock);

	/*
	 * Process chunks (and associated exceptions) in reverse order
	 * so that dm_consecutive_chunk_count_dec() accounting works.
	 */
	do {
		r = __remove_single_exception_chunk(s, old_chunk);
		if (r)
			goto out;
	} while (old_chunk-- > s->first_merging_chunk);

	b = __release_queued_bios_after_merge(s);

out:
	up_write(&s->lock);
	if (b)
		flush_bios(b);

	return r;
}