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
struct cardstate {TYPE_1__* ops; scalar_t__ ignoreframes; } ;
struct bc_state {int channel; int use_count; int /*<<< orphan*/ * skb; int /*<<< orphan*/ ** commands; scalar_t__ ignore; scalar_t__ busy; scalar_t__ chstate; struct cardstate* cs; int /*<<< orphan*/  inputstate; int /*<<< orphan*/  fcs; scalar_t__ emptycount; int /*<<< orphan*/  at_state; scalar_t__ trans_up; scalar_t__ trans_down; scalar_t__ corrupted; int /*<<< orphan*/  squeue; int /*<<< orphan*/ * tx_skb; } ;
struct TYPE_2__ {scalar_t__ (* initbcshw ) (struct bc_state*) ;} ;

/* Variables and functions */
 int AT_NUM ; 
 int /*<<< orphan*/  DEBUG_INIT ; 
 scalar_t__ HW_HDR_LEN ; 
 int /*<<< orphan*/  INS_skip_frame ; 
 int /*<<< orphan*/  PPP_INITFCS ; 
 scalar_t__ SBUFSIZE ; 
 int /*<<< orphan*/ * dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gigaset_at_init (int /*<<< orphan*/ *,struct bc_state*,struct cardstate*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reserve (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ stub1 (struct bc_state*) ; 

__attribute__((used)) static struct bc_state *gigaset_initbcs(struct bc_state *bcs,
					struct cardstate *cs, int channel)
{
	int i;

	bcs->tx_skb = NULL; //FIXME -> hw part

	skb_queue_head_init(&bcs->squeue);

	bcs->corrupted = 0;
	bcs->trans_down = 0;
	bcs->trans_up = 0;

	gig_dbg(DEBUG_INIT, "setting up bcs[%d]->at_state", channel);
	gigaset_at_init(&bcs->at_state, bcs, cs, -1);

#ifdef CONFIG_GIGASET_DEBUG
	bcs->emptycount = 0;
#endif

	gig_dbg(DEBUG_INIT, "allocating bcs[%d]->skb", channel);
	bcs->fcs = PPP_INITFCS;
	bcs->inputstate = 0;
	if (cs->ignoreframes) {
		bcs->inputstate |= INS_skip_frame;
		bcs->skb = NULL;
	} else if ((bcs->skb = dev_alloc_skb(SBUFSIZE + HW_HDR_LEN)) != NULL)
		skb_reserve(bcs->skb, HW_HDR_LEN);
	else {
		pr_err("out of memory\n");
		bcs->inputstate |= INS_skip_frame;
	}

	bcs->channel = channel;
	bcs->cs = cs;

	bcs->chstate = 0;
	bcs->use_count = 1;
	bcs->busy = 0;
	bcs->ignore = cs->ignoreframes;

	for (i = 0; i < AT_NUM; ++i)
		bcs->commands[i] = NULL;

	gig_dbg(DEBUG_INIT, "  setting up bcs[%d]->hw", channel);
	if (cs->ops->initbcshw(bcs))
		return bcs;

	gig_dbg(DEBUG_INIT, "  failed");

	gig_dbg(DEBUG_INIT, "  freeing bcs[%d]->skb", channel);
	if (bcs->skb)
		dev_kfree_skb(bcs->skb);

	return NULL;
}