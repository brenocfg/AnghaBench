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
struct sh_cmt_priv {unsigned long flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  max_match_value; } ;

/* Variables and functions */
 unsigned long FLAG_CLOCKEVENT ; 
 unsigned long FLAG_CLOCKSOURCE ; 
 int /*<<< orphan*/  sh_cmt_disable (struct sh_cmt_priv*) ; 
 int /*<<< orphan*/  sh_cmt_set_next (struct sh_cmt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sh_cmt_stop(struct sh_cmt_priv *p, unsigned long flag)
{
	unsigned long flags;
	unsigned long f;

	spin_lock_irqsave(&p->lock, flags);

	f = p->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE);
	p->flags &= ~flag;

	if (f && !(p->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE)))
		sh_cmt_disable(p);

	/* adjust the timeout to maximum if only clocksource left */
	if ((flag == FLAG_CLOCKEVENT) && (p->flags & FLAG_CLOCKSOURCE))
		sh_cmt_set_next(p, p->max_match_value);

	spin_unlock_irqrestore(&p->lock, flags);
}