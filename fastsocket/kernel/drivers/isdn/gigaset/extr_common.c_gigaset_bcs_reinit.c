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
struct sk_buff {int dummy; } ;
struct cardstate {TYPE_1__* ops; int /*<<< orphan*/  ignoreframes; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int cid; scalar_t__ timer_expires; scalar_t__ timer_active; scalar_t__ ConState; } ;
struct bc_state {int /*<<< orphan*/  inputstate; int /*<<< orphan*/  ignore; scalar_t__ chstate; int /*<<< orphan*/  fcs; scalar_t__ emptycount; TYPE_2__ at_state; int /*<<< orphan*/  squeue; struct cardstate* cs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reinitbcshw ) (struct bc_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INS_skip_frame ; 
 int /*<<< orphan*/  PPP_INITFCS ; 
 int /*<<< orphan*/  clear_at_state (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct bc_state*) ; 

void gigaset_bcs_reinit(struct bc_state *bcs)
{
	struct sk_buff *skb;
	struct cardstate *cs = bcs->cs;
	unsigned long flags;

	while ((skb = skb_dequeue(&bcs->squeue)) != NULL)
		dev_kfree_skb(skb);

	spin_lock_irqsave(&cs->lock, flags);
	clear_at_state(&bcs->at_state);
	bcs->at_state.ConState = 0;
	bcs->at_state.timer_active = 0;
	bcs->at_state.timer_expires = 0;
	bcs->at_state.cid = -1;			/* No CID defined */
	spin_unlock_irqrestore(&cs->lock, flags);

	bcs->inputstate = 0;

#ifdef CONFIG_GIGASET_DEBUG
	bcs->emptycount = 0;
#endif

	bcs->fcs = PPP_INITFCS;
	bcs->chstate = 0;

	bcs->ignore = cs->ignoreframes;
	if (bcs->ignore)
		bcs->inputstate |= INS_skip_frame;


	cs->ops->reinitbcshw(bcs);
}