#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* dq_op; } ;
struct dquot {unsigned int dq_id; int /*<<< orphan*/  dq_sb; int /*<<< orphan*/  dq_flags; int /*<<< orphan*/  dq_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  lookups; int /*<<< orphan*/  cache_hits; } ;
struct TYPE_3__ {scalar_t__ (* acquire_dquot ) (struct dquot*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DQ_ACTIVE_B ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_destroy_dquot (struct dquot*) ; 
 int /*<<< orphan*/  dq_list_lock ; 
 int /*<<< orphan*/  dq_state_lock ; 
 int /*<<< orphan*/  dqput (struct dquot*) ; 
 TYPE_2__ dqstats ; 
 struct dquot* find_dquot (unsigned int,struct super_block*,unsigned int,int) ; 
 struct dquot* get_empty_dquot (struct super_block*,int) ; 
 unsigned int hashfn (struct super_block*,unsigned int,int) ; 
 int /*<<< orphan*/  insert_dquot_hash (struct dquot*) ; 
 int /*<<< orphan*/  put_inuse (struct dquot*) ; 
 int /*<<< orphan*/  remove_free_dquot (struct dquot*) ; 
 int /*<<< orphan*/  sb_has_quota_active (struct super_block*,int) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dquot*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_dquot (struct dquot*) ; 

struct dquot *dqget(struct super_block *sb, unsigned int id, int type)
{
	unsigned int hashent = hashfn(sb, id, type);
	struct dquot *dquot = NULL, *empty = NULL;

        if (!sb_has_quota_active(sb, type))
		return NULL;
we_slept:
	spin_lock(&dq_list_lock);
	spin_lock(&dq_state_lock);
	if (!sb_has_quota_active(sb, type)) {
		spin_unlock(&dq_state_lock);
		spin_unlock(&dq_list_lock);
		goto out;
	}
	spin_unlock(&dq_state_lock);

	dquot = find_dquot(hashent, sb, id, type);
	if (!dquot) {
		if (!empty) {
			spin_unlock(&dq_list_lock);
			empty = get_empty_dquot(sb, type);
			if (!empty)
				schedule();	/* Try to wait for a moment... */
			goto we_slept;
		}
		dquot = empty;
		empty = NULL;
		dquot->dq_id = id;
		/* all dquots go on the inuse_list */
		put_inuse(dquot);
		/* hash it first so it can be found */
		insert_dquot_hash(dquot);
		dqstats.lookups++;
		spin_unlock(&dq_list_lock);
	} else {
		if (!atomic_read(&dquot->dq_count))
			remove_free_dquot(dquot);
		atomic_inc(&dquot->dq_count);
		dqstats.cache_hits++;
		dqstats.lookups++;
		spin_unlock(&dq_list_lock);
	}
	/* Wait for dq_lock - after this we know that either dquot_release() is
	 * already finished or it will be canceled due to dq_count > 1 test */
	wait_on_dquot(dquot);
	/* Read the dquot / allocate space in quota file */
	if (!test_bit(DQ_ACTIVE_B, &dquot->dq_flags) &&
	    sb->dq_op->acquire_dquot(dquot) < 0) {
		dqput(dquot);
		dquot = NULL;
		goto out;
	}
#ifdef CONFIG_QUOTA_DEBUG
	BUG_ON(!dquot->dq_sb);	/* Has somebody invalidated entry under us? */
#endif
out:
	if (empty)
		do_destroy_dquot(empty);

	return dquot;
}