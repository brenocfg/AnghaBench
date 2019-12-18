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

/* Variables and functions */
 int /*<<< orphan*/  __nfs4_state_shutdown () ; 
 int /*<<< orphan*/  cancel_rearming_delayed_workqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  laundromat_work ; 
 int /*<<< orphan*/  laundry_wq ; 
 int /*<<< orphan*/  locks_end_grace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_release_reclaim () ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 int /*<<< orphan*/  nfsd4_destroy_callback_queue () ; 
 int /*<<< orphan*/  nfsd4_manager ; 

void
nfs4_state_shutdown(void)
{
	cancel_rearming_delayed_workqueue(laundry_wq, &laundromat_work);
	destroy_workqueue(laundry_wq);
	locks_end_grace(&nfsd4_manager);
	nfs4_lock_state();
	nfs4_release_reclaim();
	__nfs4_state_shutdown();
	nfs4_unlock_state();
	nfsd4_destroy_callback_queue();
}