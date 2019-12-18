#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer_mod; } ;
struct bfad_s {int /*<<< orphan*/  hal_tmo; int /*<<< orphan*/  bfad_lock; TYPE_1__ bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TIMER_FREQ ; 
 int /*<<< orphan*/  bfa_comp_deq (TYPE_1__*,struct list_head*) ; 
 int /*<<< orphan*/  bfa_comp_free (TYPE_1__*,struct list_head*) ; 
 int /*<<< orphan*/  bfa_comp_process (TYPE_1__*,struct list_head*) ; 
 int /*<<< orphan*/  bfa_timer_beat (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
bfad_bfa_tmo(unsigned long data)
{
	struct bfad_s	      *bfad = (struct bfad_s *) data;
	unsigned long	flags;
	struct list_head	       doneq;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	bfa_timer_beat(&bfad->bfa.timer_mod);

	bfa_comp_deq(&bfad->bfa, &doneq);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (!list_empty(&doneq)) {
		bfa_comp_process(&bfad->bfa, &doneq);
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfa_comp_free(&bfad->bfa, &doneq);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	}

	mod_timer(&bfad->hal_tmo,
		  jiffies + msecs_to_jiffies(BFA_TIMER_FREQ));
}