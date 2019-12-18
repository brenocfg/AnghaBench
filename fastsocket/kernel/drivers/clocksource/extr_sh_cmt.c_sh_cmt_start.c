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
struct sh_cmt_priv {unsigned long flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  max_match_value; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 unsigned long FLAG_CLOCKEVENT ; 
 unsigned long FLAG_CLOCKSOURCE ; 
 int sh_cmt_enable (struct sh_cmt_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_cmt_set_next (struct sh_cmt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh_cmt_start(struct sh_cmt_priv *p, unsigned long flag)
{
	int ret = 0;
	unsigned long flags;

	spin_lock_irqsave(&p->lock, flags);

	if (!(p->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE)))
		ret = sh_cmt_enable(p, &p->rate);

	if (ret)
		goto out;
	p->flags |= flag;

	/* setup timeout if no clockevent */
	if ((flag == FLAG_CLOCKSOURCE) && (!(p->flags & FLAG_CLOCKEVENT)))
		sh_cmt_set_next(p, p->max_match_value);
 out:
	spin_unlock_irqrestore(&p->lock, flags);

	return ret;
}