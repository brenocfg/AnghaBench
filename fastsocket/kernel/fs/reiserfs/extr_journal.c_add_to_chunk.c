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
struct buffer_head {int dummy; } ;
struct buffer_chunk {scalar_t__ nr; struct buffer_head** bh; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CHUNK_SIZE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_to_chunk(struct buffer_chunk *chunk, struct buffer_head *bh,
			spinlock_t * lock, void (fn) (struct buffer_chunk *))
{
	int ret = 0;
	BUG_ON(chunk->nr >= CHUNK_SIZE);
	chunk->bh[chunk->nr++] = bh;
	if (chunk->nr >= CHUNK_SIZE) {
		ret = 1;
		if (lock)
			spin_unlock(lock);
		fn(chunk);
		if (lock)
			spin_lock(lock);
	}
	return ret;
}