#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mode; } ;
struct pool_c {TYPE_3__ adjusted_pf; } ;
struct TYPE_5__ {int mode; } ;
struct pool {TYPE_2__ pf; void* process_prepared_discard; void* process_prepared_mapping; void* process_discard; void* process_bio; int /*<<< orphan*/  pmd; int /*<<< orphan*/  pool_md; TYPE_1__* ti; } ;
typedef  enum pool_mode { ____Placeholder_pool_mode } pool_mode ;
struct TYPE_4__ {struct pool_c* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
#define  PM_FAIL 131 
#define  PM_OUT_OF_DATA_SPACE 130 
#define  PM_READ_ONLY 129 
#define  PM_WRITE 128 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int dm_pool_metadata_needs_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_pool_metadata_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_pool_metadata_read_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_retry_list (struct pool*) ; 
 int get_pool_mode (struct pool*) ; 
 int /*<<< orphan*/  notify_of_pool_mode_change (struct pool*,char*) ; 
 void* process_bio ; 
 void* process_bio_fail ; 
 void* process_bio_read_only ; 
 void* process_bio_success ; 
 void* process_discard ; 
 void* process_prepared_discard ; 
 void* process_prepared_discard_fail ; 
 void* process_prepared_discard_passdown ; 
 void* process_prepared_mapping ; 
 void* process_prepared_mapping_fail ; 

__attribute__((used)) static void set_pool_mode(struct pool *pool, enum pool_mode new_mode)
{
	struct pool_c *pt = pool->ti->private;
	bool needs_check = dm_pool_metadata_needs_check(pool->pmd);
	enum pool_mode old_mode = get_pool_mode(pool);

	/*
	 * Never allow the pool to transition to PM_WRITE mode if user
	 * intervention is required to verify metadata and data consistency.
	 */
	if (new_mode == PM_WRITE && needs_check) {
		DMERR("%s: unable to switch pool to write mode until repaired.",
		      dm_device_name(pool->pool_md));
		if (old_mode != new_mode)
			new_mode = old_mode;
		else
			new_mode = PM_READ_ONLY;
	}
	/*
	 * If we were in PM_FAIL mode, rollback of metadata failed.  We're
	 * not going to recover without a thin_repair.	So we never let the
	 * pool move out of the old mode.
	 */
	if (old_mode == PM_FAIL)
		new_mode = old_mode;

	switch (new_mode) {
	case PM_FAIL:
		if (old_mode != new_mode)
			notify_of_pool_mode_change(pool, "failure");
		dm_pool_metadata_read_only(pool->pmd);
		pool->process_bio = process_bio_fail;
		pool->process_discard = process_bio_fail;
		pool->process_prepared_mapping = process_prepared_mapping_fail;
		pool->process_prepared_discard = process_prepared_discard_fail;

		error_retry_list(pool);
		break;

	case PM_READ_ONLY:
		if (old_mode != new_mode)
			notify_of_pool_mode_change(pool, "read-only");
		dm_pool_metadata_read_only(pool->pmd);
		pool->process_bio = process_bio_read_only;
		pool->process_discard = process_bio_success;
		pool->process_prepared_mapping = process_prepared_mapping_fail;
		pool->process_prepared_discard = process_prepared_discard_passdown;

		error_retry_list(pool);
		break;

	case PM_OUT_OF_DATA_SPACE:
		/*
		 * Ideally we'd never hit this state; the low water mark
		 * would trigger userland to extend the pool before we
		 * completely run out of data space.  However, many small
		 * IOs to unprovisioned space can consume data space at an
		 * alarming rate.  Adjust your low water mark if you're
		 * frequently seeing this mode.
		 */
		if (old_mode != new_mode)
			notify_of_pool_mode_change(pool, "out-of-data-space");
		pool->process_bio = process_bio_read_only;
		pool->process_discard = process_discard;
		pool->process_prepared_mapping = process_prepared_mapping;
		pool->process_prepared_discard = process_prepared_discard_passdown;
		break;

	case PM_WRITE:
		if (old_mode != new_mode)
			notify_of_pool_mode_change(pool, "write");
		dm_pool_metadata_read_write(pool->pmd);
		pool->process_bio = process_bio;
		pool->process_discard = process_discard;
		pool->process_prepared_mapping = process_prepared_mapping;
		pool->process_prepared_discard = process_prepared_discard;
		break;
	}

	pool->pf.mode = new_mode;
	/*
	 * The pool mode may have changed, sync it so bind_control_target()
	 * doesn't cause an unexpected mode transition on resume.
	 */
	pt->adjusted_pf.mode = new_mode;
}