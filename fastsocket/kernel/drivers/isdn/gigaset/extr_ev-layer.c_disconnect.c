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
struct TYPE_3__ {int /*<<< orphan*/  pending_commands; } ;
struct cardstate {int commands_pending; int /*<<< orphan*/  lock; TYPE_2__* ops; TYPE_1__ at_state; int /*<<< orphan*/  cidmode; } ;
struct bc_state {int chstate; } ;
struct at_state_t {int /*<<< orphan*/  list; int /*<<< orphan*/  seq_index; struct cardstate* cs; struct bc_state* bcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* close_bchannel ) (struct bc_state*) ;} ;

/* Variables and functions */
 int CHS_D_UP ; 
 int CHS_NOTIFY_LL ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  ISDN_STAT_DHUP ; 
 int /*<<< orphan*/  PC_UMMODE ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_i4l_channel_cmd (struct bc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct at_state_t*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct bc_state*) ; 

__attribute__((used)) static void disconnect(struct at_state_t **at_state_p)
{
	unsigned long flags;
	struct bc_state *bcs = (*at_state_p)->bcs;
	struct cardstate *cs = (*at_state_p)->cs;

	spin_lock_irqsave(&cs->lock, flags);
	++(*at_state_p)->seq_index;

	/* revert to selected idle mode */
	if (!cs->cidmode) {
		cs->at_state.pending_commands |= PC_UMMODE;
		cs->commands_pending = 1;
		gig_dbg(DEBUG_CMD, "Scheduling PC_UMMODE");
	}
	spin_unlock_irqrestore(&cs->lock, flags);

	if (bcs) {
		/* B channel assigned: invoke hardware specific handler */
		cs->ops->close_bchannel(bcs);
		/* notify LL */
		if (bcs->chstate & (CHS_D_UP | CHS_NOTIFY_LL)) {
			bcs->chstate &= ~(CHS_D_UP | CHS_NOTIFY_LL);
			gigaset_i4l_channel_cmd(bcs, ISDN_STAT_DHUP);
		}
	} else {
		/* no B channel assigned: just deallocate */
		spin_lock_irqsave(&cs->lock, flags);
		list_del(&(*at_state_p)->list);
		kfree(*at_state_p);
		*at_state_p = NULL;
		spin_unlock_irqrestore(&cs->lock, flags);
	}
}