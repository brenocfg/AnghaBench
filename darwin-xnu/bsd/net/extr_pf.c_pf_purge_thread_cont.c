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
typedef  int u_int32_t ;
struct TYPE_4__ {int* timeout; } ;
struct TYPE_3__ {int states; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 size_t PFTM_INTERVAL ; 
 int /*<<< orphan*/  PWAIT ; 
 scalar_t__ RB_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int hz ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_update_uptime () ; 
 TYPE_2__ pf_default_rule ; 
 int /*<<< orphan*/  pf_lock ; 
 scalar_t__ pf_normalize_isempty () ; 
 int /*<<< orphan*/  pf_perim_lock ; 
 int /*<<< orphan*/  pf_purge_expired_fragments () ; 
 int /*<<< orphan*/  pf_purge_expired_src_nodes () ; 
 int /*<<< orphan*/  pf_purge_expired_states (int) ; 
 int /*<<< orphan*/ * pf_purge_thread ; 
 int /*<<< orphan*/  pf_purge_thread_fn ; 
 TYPE_1__ pf_status ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_src_tracking ; 
 int /*<<< orphan*/  tsleep0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int (*) (int)) ; 

__attribute__((used)) static int
pf_purge_thread_cont(int err)
{
#pragma unused(err)
	static u_int32_t nloops = 0;
	int t = 1;	/* 1 second */

	/*
	 * Update coarse-grained networking timestamp (in sec.); the idea
	 * is to piggy-back on the periodic timeout callout to update
	 * the counter returnable via net_uptime().
	 */
	net_update_uptime();

	lck_rw_lock_shared(pf_perim_lock);
	lck_mtx_lock(pf_lock);

	/* purge everything if not running */
	if (!pf_status.running) {
		pf_purge_expired_states(pf_status.states);
		pf_purge_expired_fragments();
		pf_purge_expired_src_nodes();

		/* terminate thread (we don't currently do this) */
		if (pf_purge_thread == NULL) {
			lck_mtx_unlock(pf_lock);
			lck_rw_done(pf_perim_lock);

			thread_deallocate(current_thread());
			thread_terminate(current_thread());
			/* NOTREACHED */
			return (0);
		} else {
			/* if there's nothing left, sleep w/o timeout */
			if (pf_status.states == 0 &&
			    pf_normalize_isempty() &&
			    RB_EMPTY(&tree_src_tracking)) {
				nloops = 0;
				t = 0;
			}
			goto done;
		}
	}

	/* process a fraction of the state table every second */
	pf_purge_expired_states(1 + (pf_status.states
	    / pf_default_rule.timeout[PFTM_INTERVAL]));

	/* purge other expired types every PFTM_INTERVAL seconds */
	if (++nloops >= pf_default_rule.timeout[PFTM_INTERVAL]) {
		pf_purge_expired_fragments();
		pf_purge_expired_src_nodes();
		nloops = 0;
	}
done:
	lck_mtx_unlock(pf_lock);
	lck_rw_done(pf_perim_lock);

	(void) tsleep0(pf_purge_thread_fn, PWAIT, "pf_purge_cont",
	    t * hz, pf_purge_thread_cont);
	/* NOTREACHED */
	VERIFY(0);

	return (0);
}