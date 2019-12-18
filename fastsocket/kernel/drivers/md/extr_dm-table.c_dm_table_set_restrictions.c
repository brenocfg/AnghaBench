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
struct queue_limits {scalar_t__ discard_zeroes_data; scalar_t__ no_cluster; } ;
struct request_queue {struct queue_limits limits; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_ADD_RANDOM ; 
 int /*<<< orphan*/  QUEUE_FLAG_CLUSTER ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  QUEUE_FLAG_STACKABLE ; 
 unsigned int REQ_FLUSH ; 
 unsigned int REQ_FUA ; 
 scalar_t__ blk_queue_add_random (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flush (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  device_is_nonrot ; 
 int /*<<< orphan*/  device_is_not_random ; 
 scalar_t__ dm_table_all_devices_attribute (struct dm_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_discard_zeroes_data (struct dm_table*) ; 
 scalar_t__ dm_table_request_based (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_set_integrity (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_supports_discards (struct dm_table*) ; 
 scalar_t__ dm_table_supports_flush (struct dm_table*,unsigned int) ; 
 int /*<<< orphan*/  queue_flag_clear_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  smp_mb () ; 

void dm_table_set_restrictions(struct dm_table *t, struct request_queue *q,
			       struct queue_limits *limits)
{
	unsigned flush = 0;

	/*
	 * Copy table's limits to the DM device's request_queue
	 */
	q->limits = *limits;

	if (limits->no_cluster)
		queue_flag_clear_unlocked(QUEUE_FLAG_CLUSTER, q);
	else
		queue_flag_set_unlocked(QUEUE_FLAG_CLUSTER, q);

	if (!dm_table_supports_discards(t))
		queue_flag_clear_unlocked(QUEUE_FLAG_DISCARD, q);
	else
		queue_flag_set_unlocked(QUEUE_FLAG_DISCARD, q);

	if (dm_table_supports_flush(t, REQ_FLUSH)) {
		flush |= REQ_FLUSH;
		if (dm_table_supports_flush(t, REQ_FUA))
			flush |= REQ_FUA;
	}
	blk_queue_flush(q, flush);

	if (!dm_table_discard_zeroes_data(t))
		q->limits.discard_zeroes_data = 0;

	/* Ensure that all underlying devices are non-rotational. */
	if (dm_table_all_devices_attribute(t, device_is_nonrot))
		queue_flag_set_unlocked(QUEUE_FLAG_NONROT, q);
	else
		queue_flag_clear_unlocked(QUEUE_FLAG_NONROT, q);

	dm_table_set_integrity(t);

	/*
	 * Determine whether or not this queue's I/O timings contribute
	 * to the entropy pool, Only request-based targets use this.
	 * Clear QUEUE_FLAG_ADD_RANDOM if any underlying device does not
	 * have it set.
	 */
	if (blk_queue_add_random(q) && dm_table_all_devices_attribute(t, device_is_not_random))
		queue_flag_clear_unlocked(QUEUE_FLAG_ADD_RANDOM, q);

	/*
	 * QUEUE_FLAG_STACKABLE must be set after all queue settings are
	 * visible to other CPUs because, once the flag is set, incoming bios
	 * are processed by request-based dm, which refers to the queue
	 * settings.
	 * Until the flag set, bios are passed to bio-based dm and queued to
	 * md->deferred where queue settings are not needed yet.
	 * Those bios are passed to request-based dm at the resume time.
	 */
	smp_mb();
	if (dm_table_request_based(t))
		queue_flag_set_unlocked(QUEUE_FLAG_STACKABLE, q);
}