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
struct dquot {scalar_t__ dq_cnt; int dq_flags; } ;

/* Variables and functions */
 int DQ_MOD ; 
 struct dquot* NODQUOT ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dq_freelist ; 
 int /*<<< orphan*/  dq_list_lock () ; 
 int /*<<< orphan*/  dq_list_unlock () ; 
 int /*<<< orphan*/  dq_lock_internal (struct dquot*) ; 
 int /*<<< orphan*/  dq_unlock_internal (struct dquot*) ; 
 int /*<<< orphan*/  dqdirtylist ; 
 int /*<<< orphan*/  dqfreelist ; 

void
dqreclaim(struct dquot *dq)
{

	if (dq == NODQUOT)
		return;

	dq_list_lock();
	dq_lock_internal(dq);

	if (--dq->dq_cnt > 0) {
	        dq_unlock_internal(dq);
		dq_list_unlock();
		return;
	}
	if (dq->dq_flags & DQ_MOD)
		TAILQ_INSERT_TAIL(&dqdirtylist, dq, dq_freelist);
	else
		TAILQ_INSERT_TAIL(&dqfreelist, dq, dq_freelist);

	dq_unlock_internal(dq);
	dq_list_unlock();
}