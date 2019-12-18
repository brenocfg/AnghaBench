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
struct cmdbuf_t {struct cmdbuf_t* next; } ;
struct cardstate {int gotfwver; int channels; int /*<<< orphan*/  waitqueue; scalar_t__ waiting; int /*<<< orphan*/  cmd_result; scalar_t__ bcs; int /*<<< orphan*/  lock; scalar_t__ cbytes; scalar_t__ commands_pending; scalar_t__ cur_at_seq; scalar_t__ dle; scalar_t__ cmdbytes; scalar_t__ curlen; int /*<<< orphan*/ * lastcmdbuf; struct cmdbuf_t* cmdbuf; TYPE_1__* inbuf; int /*<<< orphan*/  at_state; int /*<<< orphan*/  mstate; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/  inputstate; struct cmdbuf_t* rcvbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  INS_command ; 
 int /*<<< orphan*/  MS_UNINITIALIZED ; 
 int /*<<< orphan*/  M_UNKNOWN ; 
 int /*<<< orphan*/  clear_at_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dealloc_at_states (struct cardstate*) ; 
 int /*<<< orphan*/  free_strings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gigaset_at_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gigaset_freebcs (scalar_t__) ; 
 int /*<<< orphan*/  gigaset_initbcs (scalar_t__,struct cardstate*,int) ; 
 int /*<<< orphan*/  kfree (struct cmdbuf_t*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_cs(struct cardstate *cs)
{
	struct cmdbuf_t *cb, *tcb;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&cs->lock, flags);

	cs->mode = M_UNKNOWN;
	cs->mstate = MS_UNINITIALIZED;

	clear_at_state(&cs->at_state);
	dealloc_at_states(cs);
	free_strings(&cs->at_state);
	gigaset_at_init(&cs->at_state, NULL, cs, 0);

	kfree(cs->inbuf->rcvbuf);
	cs->inbuf->rcvbuf = NULL;
	cs->inbuf->inputstate = INS_command;
	cs->inbuf->head = 0;
	cs->inbuf->tail = 0;

	cb = cs->cmdbuf;
	while (cb) {
		tcb = cb;
		cb = cb->next;
		kfree(tcb);
	}
	cs->cmdbuf = cs->lastcmdbuf = NULL;
	cs->curlen = 0;
	cs->cmdbytes = 0;
	cs->gotfwver = -1;
	cs->dle = 0;
	cs->cur_at_seq = 0;
	cs->commands_pending = 0;
	cs->cbytes = 0;

	spin_unlock_irqrestore(&cs->lock, flags);

	for (i = 0; i < cs->channels; ++i) {
		gigaset_freebcs(cs->bcs + i);
		if (!gigaset_initbcs(cs->bcs + i, cs, i))
			pr_err("could not allocate channel %d data\n", i);
	}

	if (cs->waiting) {
		cs->cmd_result = -ENODEV;
		cs->waiting = 0;
		wake_up_interruptible(&cs->waitqueue);
	}
}