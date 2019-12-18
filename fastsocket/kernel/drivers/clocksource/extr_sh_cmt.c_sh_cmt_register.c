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
struct sh_cmt_priv {int width; int max_match_value; int match_value; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  sh_cmt_register_clockevent (struct sh_cmt_priv*,char*,unsigned long) ; 
 int /*<<< orphan*/  sh_cmt_register_clocksource (struct sh_cmt_priv*,char*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sh_cmt_register(struct sh_cmt_priv *p, char *name,
			   unsigned long clockevent_rating,
			   unsigned long clocksource_rating)
{
	if (p->width == (sizeof(p->max_match_value) * 8))
		p->max_match_value = ~0;
	else
		p->max_match_value = (1 << p->width) - 1;

	p->match_value = p->max_match_value;
	spin_lock_init(&p->lock);

	if (clockevent_rating)
		sh_cmt_register_clockevent(p, name, clockevent_rating);

	if (clocksource_rating)
		sh_cmt_register_clocksource(p, name, clocksource_rating);

	return 0;
}