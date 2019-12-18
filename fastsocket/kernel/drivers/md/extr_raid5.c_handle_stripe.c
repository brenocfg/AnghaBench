#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stripe_head_state {int uptodate; scalar_t__ failed; size_t* failed_num; int dec_preread_active; int p_failed; int q_failed; int compute; int /*<<< orphan*/  return_bi; scalar_t__ ops_request; scalar_t__ handle_bad_blocks; struct md_rdev* blocked_rdev; int /*<<< orphan*/  locked; scalar_t__ expanding; scalar_t__ expanded; scalar_t__ replacing; scalar_t__ syncing; scalar_t__ to_write; scalar_t__ non_overwrite; scalar_t__ to_read; scalar_t__ written; scalar_t__ to_fill; } ;
struct stripe_head {int disks; size_t pd_idx; scalar_t__ qd_idx; scalar_t__ reconstruct_state; scalar_t__ sector; struct r5dev* dev; int /*<<< orphan*/  lock; scalar_t__ state; scalar_t__ check_state; int /*<<< orphan*/  count; int /*<<< orphan*/  stripe_lock; struct r5conf* raid_conf; } ;
struct r5dev {scalar_t__ flags; scalar_t__ written; } ;
struct r5conf {scalar_t__ max_degraded; int level; int raid_disks; TYPE_2__* mddev; int /*<<< orphan*/  preread_active_stripes; TYPE_1__* disks; int /*<<< orphan*/  wait_for_overlap; int /*<<< orphan*/  reshape_stripes; } ;
struct md_rdev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  thread; scalar_t__ external; int /*<<< orphan*/  ro; } ;
struct TYPE_6__ {struct md_rdev* rdev; struct md_rdev* replacement; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IO_THRESHOLD ; 
 int /*<<< orphan*/  R5_Discard ; 
 int /*<<< orphan*/  R5_Insync ; 
 int /*<<< orphan*/  R5_LOCKED ; 
 int /*<<< orphan*/  R5_MadeGood ; 
 int /*<<< orphan*/  R5_MadeGoodRepl ; 
 int /*<<< orphan*/  R5_NeedReplace ; 
 int /*<<< orphan*/  R5_Overlap ; 
 int /*<<< orphan*/  R5_ReWrite ; 
 int /*<<< orphan*/  R5_ReadError ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  R5_WantReplace ; 
 int /*<<< orphan*/  R5_Wantread ; 
 int /*<<< orphan*/  R5_Wantwrite ; 
 int /*<<< orphan*/  R5_WriteError ; 
 int /*<<< orphan*/  STRIPE_BIOFILL_RUN ; 
 int /*<<< orphan*/  STRIPE_COMPUTE_RUN ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_DISCARD ; 
 int /*<<< orphan*/  STRIPE_EXPANDING ; 
 int /*<<< orphan*/  STRIPE_EXPAND_READY ; 
 int /*<<< orphan*/  STRIPE_EXPAND_SOURCE ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_INSYNC ; 
 int /*<<< orphan*/  STRIPE_OP_BIOFILL ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 int /*<<< orphan*/  STRIPE_REPLACED ; 
 int /*<<< orphan*/  STRIPE_SECTORS ; 
 int /*<<< orphan*/  STRIPE_SYNCING ; 
 int /*<<< orphan*/  STRIPE_SYNC_REQUESTED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  analyse_stripe (struct stripe_head*,struct stripe_head_state*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 struct stripe_head* get_active_stripe (struct r5conf*,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  handle_failed_stripe (struct r5conf*,struct stripe_head*,struct stripe_head_state*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_failed_sync (struct r5conf*,struct stripe_head*,struct stripe_head_state*) ; 
 int /*<<< orphan*/  handle_parity_checks5 (struct r5conf*,struct stripe_head*,struct stripe_head_state*,int) ; 
 int /*<<< orphan*/  handle_parity_checks6 (struct r5conf*,struct stripe_head*,struct stripe_head_state*,int) ; 
 int /*<<< orphan*/  handle_stripe_clean_event (struct r5conf*,struct stripe_head*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_stripe_dirtying (struct r5conf*,struct stripe_head*,struct stripe_head_state*,int) ; 
 int /*<<< orphan*/  handle_stripe_expansion (struct r5conf*,struct stripe_head*) ; 
 int /*<<< orphan*/  handle_stripe_fill (struct stripe_head*,struct stripe_head_state*,int) ; 
 int /*<<< orphan*/  md_done_sync (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  md_error (TYPE_2__*,struct md_rdev*) ; 
 int /*<<< orphan*/  md_wait_for_blocked_rdev (struct md_rdev*,TYPE_2__*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ops_run_io (struct stripe_head*,struct stripe_head_state*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  raid_run_ops (struct stripe_head*,scalar_t__) ; 
 int /*<<< orphan*/  rdev_clear_badblocks (struct md_rdev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,TYPE_2__*) ; 
 int /*<<< orphan*/  rdev_set_badblocks (struct md_rdev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reconstruct_state_drain_result ; 
 void* reconstruct_state_idle ; 
 scalar_t__ reconstruct_state_prexor_drain_result ; 
 scalar_t__ reconstruct_state_result ; 
 int /*<<< orphan*/  release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  return_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_reconstruction (struct stripe_head*,struct stripe_head_state*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stripe_set_idx (scalar_t__,struct r5conf*,int /*<<< orphan*/ ,struct stripe_head*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ unlikely (struct md_rdev*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_stripe(struct stripe_head *sh)
{
	struct stripe_head_state s;
	struct r5conf *conf = sh->raid_conf;
	int i;
	int prexor;
	int disks = sh->disks;
	struct r5dev *pdev, *qdev;

	spin_lock(&sh->lock);

	if (test_bit(STRIPE_SYNC_REQUESTED, &sh->state)) {
		spin_lock(&sh->stripe_lock);
		/* Cannot process 'sync' concurrently with 'discard' */
		if (!test_bit(STRIPE_DISCARD, &sh->state) &&
		    test_and_clear_bit(STRIPE_SYNC_REQUESTED, &sh->state)) {
			set_bit(STRIPE_SYNCING, &sh->state);
			clear_bit(STRIPE_INSYNC, &sh->state);
			clear_bit(STRIPE_REPLACED, &sh->state);
		}
		spin_unlock(&sh->stripe_lock);
	}
	clear_bit(STRIPE_HANDLE, &sh->state);
	clear_bit(STRIPE_DELAYED, &sh->state);

	pr_debug("handling stripe %llu, state=%#lx cnt=%d, "
		"pd_idx=%d, qd_idx=%d\n, check:%d, reconstruct:%d\n",
	       (unsigned long long)sh->sector, sh->state,
	       atomic_read(&sh->count), sh->pd_idx, sh->qd_idx,
	       sh->check_state, sh->reconstruct_state);

	analyse_stripe(sh, &s);

	if (s.handle_bad_blocks) {
		set_bit(STRIPE_HANDLE, &sh->state);
		goto finish;
	}

	if (unlikely(s.blocked_rdev)) {
		if (s.syncing || s.expanding || s.expanded ||
		    s.replacing || s.to_write || s.written) {
			set_bit(STRIPE_HANDLE, &sh->state);
			goto finish;
		}
		/* There is nothing for the blocked_rdev to block */
		rdev_dec_pending(s.blocked_rdev, conf->mddev);
		s.blocked_rdev = NULL;
	}

	if (s.to_fill && !test_bit(STRIPE_BIOFILL_RUN, &sh->state)) {
		set_bit(STRIPE_OP_BIOFILL, &s.ops_request);
		set_bit(STRIPE_BIOFILL_RUN, &sh->state);
	}

	pr_debug("locked=%d uptodate=%d to_read=%d"
	       " to_write=%d failed=%d failed_num=%d,%d\n",
	       s.locked, s.uptodate, s.to_read, s.to_write, s.failed,
	       s.failed_num[0], s.failed_num[1]);
	/* check if the array has lost more than max_degraded devices and,
	 * if so, some requests might need to be failed.
	 */
	if (s.failed > conf->max_degraded) {
		sh->check_state = 0;
		sh->reconstruct_state = 0;
		if (s.to_read+s.to_write+s.written)
			handle_failed_stripe(conf, sh, &s, disks, &s.return_bi);
		if (s.syncing + s.replacing)
			handle_failed_sync(conf, sh, &s);
	}

	/* Now we check to see if any write operations have recently
	 * completed
	 */
	prexor = 0;
	if (sh->reconstruct_state == reconstruct_state_prexor_drain_result)
		prexor = 1;
	if (sh->reconstruct_state == reconstruct_state_drain_result ||
	    sh->reconstruct_state == reconstruct_state_prexor_drain_result) {
		sh->reconstruct_state = reconstruct_state_idle;

		/* All the 'written' buffers and the parity block are ready to
		 * be written back to disk
		 */
		BUG_ON(!test_bit(R5_UPTODATE, &sh->dev[sh->pd_idx].flags) &&
		       !test_bit(R5_Discard, &sh->dev[sh->pd_idx].flags));
		BUG_ON(sh->qd_idx >= 0 &&
		       !test_bit(R5_UPTODATE, &sh->dev[sh->qd_idx].flags) &&
		       !test_bit(R5_Discard, &sh->dev[sh->qd_idx].flags));
		for (i = disks; i--; ) {
			struct r5dev *dev = &sh->dev[i];
			if (test_bit(R5_LOCKED, &dev->flags) &&
				(i == sh->pd_idx || i == sh->qd_idx ||
				 dev->written)) {
				pr_debug("Writing block %d\n", i);
				set_bit(R5_Wantwrite, &dev->flags);
				if (prexor)
					continue;
				if (!test_bit(R5_Insync, &dev->flags) ||
				    ((i == sh->pd_idx || i == sh->qd_idx)  &&
				     s.failed == 0))
					set_bit(STRIPE_INSYNC, &sh->state);
			}
		}
		if (test_and_clear_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			s.dec_preread_active = 1;
	}

	/*
	 * might be able to return some write requests if the parity blocks
	 * are safe, or on a failed drive
	 */
	pdev = &sh->dev[sh->pd_idx];
	s.p_failed = (s.failed >= 1 && s.failed_num[0] == sh->pd_idx)
		|| (s.failed >= 2 && s.failed_num[1] == sh->pd_idx);
	qdev = &sh->dev[sh->qd_idx];
	s.q_failed = (s.failed >= 1 && s.failed_num[0] == sh->qd_idx)
		|| (s.failed >= 2 && s.failed_num[1] == sh->qd_idx)
		|| conf->level < 6;

	if (s.written &&
	    (s.p_failed || ((test_bit(R5_Insync, &pdev->flags)
			     && !test_bit(R5_LOCKED, &pdev->flags)
			     && (test_bit(R5_UPTODATE, &pdev->flags) ||
				 test_bit(R5_Discard, &pdev->flags))))) &&
	    (s.q_failed || ((test_bit(R5_Insync, &qdev->flags)
			     && !test_bit(R5_LOCKED, &qdev->flags)
			     && (test_bit(R5_UPTODATE, &qdev->flags) ||
				 test_bit(R5_Discard, &qdev->flags))))))
		handle_stripe_clean_event(conf, sh, disks, &s.return_bi);

	/* Now we might consider reading some blocks, either to check/generate
	 * parity, or to satisfy requests
	 * or to load a block that is being partially written.
	 */
	if (s.to_read || s.non_overwrite
	    || (conf->level == 6 && s.to_write && s.failed)
	    || (s.syncing && (s.uptodate + s.compute < disks))
	    || s.replacing
	    || s.expanding)
		handle_stripe_fill(sh, &s, disks);

	/* Now to consider new write requests and what else, if anything
	 * should be read.  We do not handle new writes when:
	 * 1/ A 'write' operation (copy+xor) is already in flight.
	 * 2/ A 'check' operation is in flight, as it may clobber the parity
	 *    block.
	 */
	if (s.to_write && !sh->reconstruct_state && !sh->check_state)
		handle_stripe_dirtying(conf, sh, &s, disks);

	/* maybe we need to check and possibly fix the parity for this stripe
	 * Any reads will already have been scheduled, so we just see if enough
	 * data is available.  The parity check is held off while parity
	 * dependent operations are in flight.
	 */
	if (sh->check_state ||
	    (s.syncing && s.locked == 0 &&
	     !test_bit(STRIPE_COMPUTE_RUN, &sh->state) &&
	     !test_bit(STRIPE_INSYNC, &sh->state))) {
		if (conf->level == 6)
			handle_parity_checks6(conf, sh, &s, disks);
		else
			handle_parity_checks5(conf, sh, &s, disks);
	}

	if ((s.replacing || s.syncing) && s.locked == 0
	    && !test_bit(STRIPE_COMPUTE_RUN, &sh->state)
	    && !test_bit(STRIPE_REPLACED, &sh->state)) {
		/* Write out to replacement devices where possible */
		for (i = 0; i < conf->raid_disks; i++)
			if (test_bit(R5_NeedReplace, &sh->dev[i].flags)) {
				WARN_ON(!test_bit(R5_UPTODATE, &sh->dev[i].flags));
				set_bit(R5_WantReplace, &sh->dev[i].flags);
				set_bit(R5_LOCKED, &sh->dev[i].flags);
				s.locked++;
			}
		if (s.replacing)
			set_bit(STRIPE_INSYNC, &sh->state);
		set_bit(STRIPE_REPLACED, &sh->state);
	}
	if ((s.syncing || s.replacing) && s.locked == 0 &&
	    !test_bit(STRIPE_COMPUTE_RUN, &sh->state) &&
	    test_bit(STRIPE_INSYNC, &sh->state)) {
		md_done_sync(conf->mddev, STRIPE_SECTORS, 1);
		clear_bit(STRIPE_SYNCING, &sh->state);
		if (test_and_clear_bit(R5_Overlap, &sh->dev[sh->pd_idx].flags))
			wake_up(&conf->wait_for_overlap);
	}

	/* If the failed drives are just a ReadError, then we might need
	 * to progress the repair/check process
	 */
	if (s.failed <= conf->max_degraded && !conf->mddev->ro)
		for (i = 0; i < s.failed; i++) {
			struct r5dev *dev = &sh->dev[s.failed_num[i]];
			if (test_bit(R5_ReadError, &dev->flags)
			    && !test_bit(R5_LOCKED, &dev->flags)
			    && test_bit(R5_UPTODATE, &dev->flags)
				) {
				if (!test_bit(R5_ReWrite, &dev->flags)) {
					set_bit(R5_Wantwrite, &dev->flags);
					set_bit(R5_ReWrite, &dev->flags);
					set_bit(R5_LOCKED, &dev->flags);
					s.locked++;
				} else {
					/* let's read it back */
					set_bit(R5_Wantread, &dev->flags);
					set_bit(R5_LOCKED, &dev->flags);
					s.locked++;
				}
			}
		}


	/* Finish reconstruct operations initiated by the expansion process */
	if (sh->reconstruct_state == reconstruct_state_result) {
		struct stripe_head *sh_src
			= get_active_stripe(conf, sh->sector, 1, 1, 1);
		if (sh_src && test_bit(STRIPE_EXPAND_SOURCE, &sh_src->state)) {
			/* sh cannot be written until sh_src has been read.
			 * so arrange for sh to be delayed a little
			 */
			set_bit(STRIPE_DELAYED, &sh->state);
			set_bit(STRIPE_HANDLE, &sh->state);
			if (!test_and_set_bit(STRIPE_PREREAD_ACTIVE,
					      &sh_src->state))
				atomic_inc(&conf->preread_active_stripes);
			release_stripe(sh_src);
			goto finish;
		}
		if (sh_src)
			release_stripe(sh_src);

		sh->reconstruct_state = reconstruct_state_idle;
		clear_bit(STRIPE_EXPANDING, &sh->state);
		for (i = conf->raid_disks; i--; ) {
			set_bit(R5_Wantwrite, &sh->dev[i].flags);
			set_bit(R5_LOCKED, &sh->dev[i].flags);
			s.locked++;
		}
	}

	if (s.expanded && test_bit(STRIPE_EXPANDING, &sh->state) &&
	    !sh->reconstruct_state) {
		/* Need to write out all blocks after computing parity */
		sh->disks = conf->raid_disks;
		stripe_set_idx(sh->sector, conf, 0, sh);
		schedule_reconstruction(sh, &s, 1, 1);
	} else if (s.expanded && !sh->reconstruct_state && s.locked == 0) {
		clear_bit(STRIPE_EXPAND_READY, &sh->state);
		atomic_dec(&conf->reshape_stripes);
		wake_up(&conf->wait_for_overlap);
		md_done_sync(conf->mddev, STRIPE_SECTORS, 1);
	}

	if (s.expanding && s.locked == 0 &&
	    !test_bit(STRIPE_COMPUTE_RUN, &sh->state))
		handle_stripe_expansion(conf, sh);

finish:
	spin_unlock(&sh->lock);

	/* wait for this device to become unblocked */
	if (unlikely(s.blocked_rdev)) {
		if (conf->mddev->external)
			md_wait_for_blocked_rdev(s.blocked_rdev,
						 conf->mddev);
		else
			/* Internal metadata will immediately
			 * be written by raid5d, so we don't
			 * need to wait here.
			 */
			rdev_dec_pending(s.blocked_rdev,
					 conf->mddev);
	}

	if (s.handle_bad_blocks)
		for (i = disks; i--; ) {
			struct md_rdev *rdev;
			struct r5dev *dev = &sh->dev[i];
			if (test_and_clear_bit(R5_WriteError, &dev->flags)) {
				/* We own a safe reference to the rdev */
				rdev = conf->disks[i].rdev;
				if (!rdev_set_badblocks(rdev, sh->sector,
							STRIPE_SECTORS, 0))
					md_error(conf->mddev, rdev);
				rdev_dec_pending(rdev, conf->mddev);
			}
			if (test_and_clear_bit(R5_MadeGood, &dev->flags)) {
				rdev = conf->disks[i].rdev;
				rdev_clear_badblocks(rdev, sh->sector,
						     STRIPE_SECTORS, 0);
				rdev_dec_pending(rdev, conf->mddev);
			}
			if (test_and_clear_bit(R5_MadeGoodRepl, &dev->flags)) {
				rdev = conf->disks[i].replacement;
				if (!rdev)
					/* rdev have been moved down */
					rdev = conf->disks[i].rdev;
				rdev_clear_badblocks(rdev, sh->sector,
						     STRIPE_SECTORS, 0);
				rdev_dec_pending(rdev, conf->mddev);
			}
		}

	if (s.ops_request)
		raid_run_ops(sh, s.ops_request);

	ops_run_io(sh, &s);

	if (s.dec_preread_active) {
		/* We delay this until after ops_run_io so that if make_request
		 * is waiting on a flush, it won't continue until the writes
		 * have actually been submitted.
		 */
		atomic_dec(&conf->preread_active_stripes);
		if (atomic_read(&conf->preread_active_stripes) <
		    IO_THRESHOLD)
			md_wakeup_thread(conf->mddev->thread);
	}

	return_io(s.return_bi);
}