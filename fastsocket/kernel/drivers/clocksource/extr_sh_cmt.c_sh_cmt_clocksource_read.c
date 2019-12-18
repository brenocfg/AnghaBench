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
struct sh_cmt_priv {unsigned long total_cycles; int /*<<< orphan*/  lock; scalar_t__ match_value; } ;
struct clocksource {int dummy; } ;
typedef  unsigned long cycle_t ;

/* Variables and functions */
 struct sh_cmt_priv* cs_to_sh_cmt (struct clocksource*) ; 
 unsigned long sh_cmt_get_counter (struct sh_cmt_priv*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static cycle_t sh_cmt_clocksource_read(struct clocksource *cs)
{
	struct sh_cmt_priv *p = cs_to_sh_cmt(cs);
	unsigned long flags, raw;
	unsigned long value;
	int has_wrapped;

	spin_lock_irqsave(&p->lock, flags);
	value = p->total_cycles;
	raw = sh_cmt_get_counter(p, &has_wrapped);

	if (unlikely(has_wrapped))
		raw += p->match_value;
	spin_unlock_irqrestore(&p->lock, flags);

	return value + raw;
}