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
struct sh_cmt_priv {unsigned long max_match_value; unsigned long next_match_value; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  sh_cmt_clock_event_program_verify (struct sh_cmt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sh_cmt_set_next(struct sh_cmt_priv *p, unsigned long delta)
{
	unsigned long flags;

	if (delta > p->max_match_value)
		pr_warning("sh_cmt: delta out of range\n");

	spin_lock_irqsave(&p->lock, flags);
	p->next_match_value = delta;
	sh_cmt_clock_event_program_verify(p, 0);
	spin_unlock_irqrestore(&p->lock, flags);
}