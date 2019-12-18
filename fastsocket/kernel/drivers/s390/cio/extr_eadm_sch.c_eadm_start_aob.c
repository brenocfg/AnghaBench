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
struct subchannel {int /*<<< orphan*/  lock; } ;
struct eadm_private {int /*<<< orphan*/  state; } ;
struct aob {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EADM_NOT_OPER ; 
 int /*<<< orphan*/  EADM_TIMEOUT ; 
 int EBUSY ; 
 int /*<<< orphan*/  SCH_TODO_EVAL ; 
 int /*<<< orphan*/  css_sched_sch_todo (struct subchannel*,int /*<<< orphan*/ ) ; 
 struct subchannel* eadm_get_idle_sch () ; 
 int /*<<< orphan*/  eadm_subchannel_set_timeout (struct subchannel*,int /*<<< orphan*/ ) ; 
 int eadm_subchannel_start (struct subchannel*,struct aob*) ; 
 struct eadm_private* get_eadm_private (struct subchannel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int eadm_start_aob(struct aob *aob)
{
	struct eadm_private *private;
	struct subchannel *sch;
	unsigned long flags;
	int ret;

	sch = eadm_get_idle_sch();
	if (!sch)
		return -EBUSY;

	spin_lock_irqsave(sch->lock, flags);
	eadm_subchannel_set_timeout(sch, EADM_TIMEOUT);
	ret = eadm_subchannel_start(sch, aob);
	if (!ret)
		goto out_unlock;

	/* Handle start subchannel failure. */
	eadm_subchannel_set_timeout(sch, 0);
	private = get_eadm_private(sch);
	private->state = EADM_NOT_OPER;
	css_sched_sch_todo(sch, SCH_TODO_EVAL);

out_unlock:
	spin_unlock_irqrestore(sch->lock, flags);

	return ret;
}