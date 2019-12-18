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
struct dm_snapshot {int /*<<< orphan*/  tracked_chunk_lock; int /*<<< orphan*/ * tracked_chunk_hash; int /*<<< orphan*/  tracked_chunk_pool; } ;
struct dm_snap_tracked_chunk {int /*<<< orphan*/  node; int /*<<< orphan*/  chunk; } ;
typedef  int /*<<< orphan*/  chunk_t ;

/* Variables and functions */
 size_t DM_TRACKED_CHUNK_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dm_snap_tracked_chunk* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dm_snap_tracked_chunk *track_chunk(struct dm_snapshot *s,
						 chunk_t chunk)
{
	struct dm_snap_tracked_chunk *c = mempool_alloc(s->tracked_chunk_pool,
							GFP_NOIO);

	c->chunk = chunk;

	spin_lock_irq(&s->tracked_chunk_lock);
	hlist_add_head(&c->node,
		       &s->tracked_chunk_hash[DM_TRACKED_CHUNK_HASH(chunk)]);
	spin_unlock_irq(&s->tracked_chunk_lock);

	return c;
}