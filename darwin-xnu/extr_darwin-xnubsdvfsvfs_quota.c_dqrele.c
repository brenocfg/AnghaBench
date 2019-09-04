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
struct dquot {int dq_cnt; int dq_flags; } ;

/* Variables and functions */
 int DQ_MOD ; 
 struct dquot* NODQUOT ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dq_freelist ; 
 int /*<<< orphan*/  dq_list_lock () ; 
 int /*<<< orphan*/  dq_list_unlock () ; 
 int /*<<< orphan*/  dq_unlock_internal (struct dquot*) ; 
 int /*<<< orphan*/  dqfreelist ; 
 int /*<<< orphan*/  dqlock (struct dquot*) ; 
 int /*<<< orphan*/  dqsync_locked (struct dquot*) ; 
 int /*<<< orphan*/  dqunlock (struct dquot*) ; 

void
dqrele(struct dquot *dq)
{

	if (dq == NODQUOT)
		return;
	dqlock(dq);

	if (dq->dq_cnt > 1) {
		dq->dq_cnt--;

		dqunlock(dq);
		return;
	}
	if (dq->dq_flags & DQ_MOD)
		(void) dqsync_locked(dq);
	dq->dq_cnt--;

	dq_list_lock();
	TAILQ_INSERT_TAIL(&dqfreelist, dq, dq_freelist);
        dq_unlock_internal(dq);
	dq_list_unlock();
}