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
struct sh_cmt_priv {unsigned long next_match_value; unsigned long max_match_value; unsigned long match_value; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMCOR ; 
 int /*<<< orphan*/  FLAG_REPROGRAM ; 
 int /*<<< orphan*/  FLAG_SKIPEVENT ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 unsigned long sh_cmt_get_counter (struct sh_cmt_priv*,int*) ; 
 int /*<<< orphan*/  sh_cmt_write (struct sh_cmt_priv*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void sh_cmt_clock_event_program_verify(struct sh_cmt_priv *p,
					      int absolute)
{
	unsigned long new_match;
	unsigned long value = p->next_match_value;
	unsigned long delay = 0;
	unsigned long now = 0;
	int has_wrapped;

	now = sh_cmt_get_counter(p, &has_wrapped);
	p->flags |= FLAG_REPROGRAM; /* force reprogram */

	if (has_wrapped) {
		/* we're competing with the interrupt handler.
		 *  -> let the interrupt handler reprogram the timer.
		 *  -> interrupt number two handles the event.
		 */
		p->flags |= FLAG_SKIPEVENT;
		return;
	}

	if (absolute)
		now = 0;

	do {
		/* reprogram the timer hardware,
		 * but don't save the new match value yet.
		 */
		new_match = now + value + delay;
		if (new_match > p->max_match_value)
			new_match = p->max_match_value;

		sh_cmt_write(p, CMCOR, new_match);

		now = sh_cmt_get_counter(p, &has_wrapped);
		if (has_wrapped && (new_match > p->match_value)) {
			/* we are changing to a greater match value,
			 * so this wrap must be caused by the counter
			 * matching the old value.
			 * -> first interrupt reprograms the timer.
			 * -> interrupt number two handles the event.
			 */
			p->flags |= FLAG_SKIPEVENT;
			break;
		}

		if (has_wrapped) {
			/* we are changing to a smaller match value,
			 * so the wrap must be caused by the counter
			 * matching the new value.
			 * -> save programmed match value.
			 * -> let isr handle the event.
			 */
			p->match_value = new_match;
			break;
		}

		/* be safe: verify hardware settings */
		if (now < new_match) {
			/* timer value is below match value, all good.
			 * this makes sure we won't miss any match events.
			 * -> save programmed match value.
			 * -> let isr handle the event.
			 */
			p->match_value = new_match;
			break;
		}

		/* the counter has reached a value greater
		 * than our new match value. and since the
		 * has_wrapped flag isn't set we must have
		 * programmed a too close event.
		 * -> increase delay and retry.
		 */
		if (delay)
			delay <<= 1;
		else
			delay = 1;

		if (!delay)
			pr_warning("sh_cmt: too long delay\n");

	} while (delay);
}