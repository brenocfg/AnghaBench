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
struct dquot {int dq_flags; } ;

/* Variables and functions */
 int DQ_MOD ; 
 struct dquot* NODQUOT ; 
 int /*<<< orphan*/  dqlock (struct dquot*) ; 
 int dqsync_locked (struct dquot*) ; 
 int /*<<< orphan*/  dqunlock (struct dquot*) ; 

int
dqsync(struct dquot *dq)
{
        int error = 0;

	if (dq != NODQUOT) {
	        dqlock(dq);

		if ( (dq->dq_flags & DQ_MOD) )
	        error = dqsync_locked(dq);

		dqunlock(dq);
	}
	return (error);
}