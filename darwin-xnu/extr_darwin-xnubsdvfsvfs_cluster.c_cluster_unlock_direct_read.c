#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ref_count; int /*<<< orphan*/  rw_lock; } ;
typedef  TYPE_1__ cl_direct_read_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  cl_direct_read_spin_lock ; 
 int /*<<< orphan*/  cl_mtx_grp ; 
 int /*<<< orphan*/  lck_rw_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 

void cluster_unlock_direct_read(cl_direct_read_lock_t *lck)
{
	lck_rw_done(&lck->rw_lock);

	lck_spin_lock(&cl_direct_read_spin_lock);
	if (lck->ref_count == 1) {
		LIST_REMOVE(lck, chain);
		lck_spin_unlock(&cl_direct_read_spin_lock);
		lck_rw_destroy(&lck->rw_lock, cl_mtx_grp);
		FREE(lck, M_TEMP);
	} else {
		--lck->ref_count;
		lck_spin_unlock(&cl_direct_read_spin_lock);
	}
}