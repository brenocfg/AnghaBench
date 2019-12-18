#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cardstate {int cs_init; int channels; int /*<<< orphan*/  mutex; scalar_t__ bcs; scalar_t__ inbuf; int /*<<< orphan*/  at_state; TYPE_1__* ops; int /*<<< orphan*/  timer; int /*<<< orphan*/  event_tasklet; int /*<<< orphan*/  lock; scalar_t__ running; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* freecshw ) (struct cardstate*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INIT ; 
 int /*<<< orphan*/  ISDN_STAT_UNLOAD ; 
 int /*<<< orphan*/  VALID_ID ; 
 int /*<<< orphan*/  clear_at_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_events (struct cardstate*) ; 
 int /*<<< orphan*/  dealloc_at_states (struct cardstate*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_cs (struct cardstate*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gigaset_free_dev_sysfs (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_freebcs (scalar_t__) ; 
 int /*<<< orphan*/  gigaset_i4l_cmd (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gigaset_if_free (struct cardstate*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  make_invalid (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct cardstate*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void gigaset_freecs(struct cardstate *cs)
{
	int i;
	unsigned long flags;

	if (!cs)
		return;

	mutex_lock(&cs->mutex);

	if (!cs->bcs)
		goto f_cs;
	if (!cs->inbuf)
		goto f_bcs;

	spin_lock_irqsave(&cs->lock, flags);
	cs->running = 0;
	spin_unlock_irqrestore(&cs->lock, flags); /* event handler and timer are
						     not rescheduled below */

	tasklet_kill(&cs->event_tasklet);
	del_timer_sync(&cs->timer);

	switch (cs->cs_init) {
	default:
		/* clear device sysfs */
		gigaset_free_dev_sysfs(cs);

		gigaset_if_free(cs);

		gig_dbg(DEBUG_INIT, "clearing hw");
		cs->ops->freecshw(cs);

		//FIXME cmdbuf

		/* fall through */
	case 2: /* error in initcshw */
		/* Deregister from LL */
		make_invalid(cs, VALID_ID);
		gig_dbg(DEBUG_INIT, "clearing iif");
		gigaset_i4l_cmd(cs, ISDN_STAT_UNLOAD);

		/* fall through */
	case 1: /* error when regestering to LL */
		gig_dbg(DEBUG_INIT, "clearing at_state");
		clear_at_state(&cs->at_state);
		dealloc_at_states(cs);

		/* fall through */
	case 0: /* error in one call to initbcs */
		for (i = 0; i < cs->channels; ++i) {
			gig_dbg(DEBUG_INIT, "clearing bcs[%d]", i);
			gigaset_freebcs(cs->bcs + i);
		}

		clear_events(cs);
		gig_dbg(DEBUG_INIT, "freeing inbuf");
		kfree(cs->inbuf);
	}
f_bcs:	gig_dbg(DEBUG_INIT, "freeing bcs[]");
	kfree(cs->bcs);
f_cs:	gig_dbg(DEBUG_INIT, "freeing cs");
	mutex_unlock(&cs->mutex);
	free_cs(cs);
}