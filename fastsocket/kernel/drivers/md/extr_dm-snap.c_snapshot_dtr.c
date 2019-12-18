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
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {int /*<<< orphan*/  origin; int /*<<< orphan*/  cow; int /*<<< orphan*/  store; int /*<<< orphan*/  pending_pool; int /*<<< orphan*/  tracked_chunk_pool; int /*<<< orphan*/ * tracked_chunk_hash; int /*<<< orphan*/  pending_exceptions_count; int /*<<< orphan*/  lock; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMERR (char*) ; 
 int DM_TRACKED_CHUNK_HASH_SIZE ; 
 int /*<<< orphan*/  __find_snapshots_sharing_cow (struct dm_snapshot*,struct dm_snapshot**,struct dm_snapshot**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __free_exceptions (struct dm_snapshot*) ; 
 int /*<<< orphan*/  _origins_lock ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_exception_store_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 scalar_t__ dm_target_is_snapshot_merge (struct dm_target*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_snapshot*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  stop_merge (struct dm_snapshot*) ; 
 int /*<<< orphan*/  unregister_snapshot (struct dm_snapshot*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snapshot_dtr(struct dm_target *ti)
{
#ifdef CONFIG_DM_DEBUG
	int i;
#endif
	struct dm_snapshot *s = ti->private;
	struct dm_snapshot *snap_src = NULL, *snap_dest = NULL;

	down_read(&_origins_lock);
	/* Check whether exception handover must be cancelled */
	(void) __find_snapshots_sharing_cow(s, &snap_src, &snap_dest, NULL);
	if (snap_src && snap_dest && (s == snap_src)) {
		down_write(&snap_dest->lock);
		snap_dest->valid = 0;
		up_write(&snap_dest->lock);
		DMERR("Cancelling snapshot handover.");
	}
	up_read(&_origins_lock);

	if (dm_target_is_snapshot_merge(ti))
		stop_merge(s);

	/* Prevent further origin writes from using this snapshot. */
	/* After this returns there can be no new kcopyd jobs. */
	unregister_snapshot(s);

	while (atomic_read(&s->pending_exceptions_count))
		msleep(1);
	/*
	 * Ensure instructions in mempool_destroy aren't reordered
	 * before atomic_read.
	 */
	smp_mb();

#ifdef CONFIG_DM_DEBUG
	for (i = 0; i < DM_TRACKED_CHUNK_HASH_SIZE; i++)
		BUG_ON(!hlist_empty(&s->tracked_chunk_hash[i]));
#endif

	mempool_destroy(s->tracked_chunk_pool);

	__free_exceptions(s);

	mempool_destroy(s->pending_pool);

	dm_exception_store_destroy(s->store);

	dm_put_device(ti, s->cow);

	dm_put_device(ti, s->origin);

	kfree(s);
}