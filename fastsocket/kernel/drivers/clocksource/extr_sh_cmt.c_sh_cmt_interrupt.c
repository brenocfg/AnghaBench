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
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;
struct sh_cmt_priv {int clear_bits; int flags; scalar_t__ match_value; scalar_t__ next_match_value; scalar_t__ max_match_value; TYPE_1__ ced; int /*<<< orphan*/  total_cycles; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CLOCK_EVT_MODE_ONESHOT ; 
 scalar_t__ CLOCK_EVT_MODE_SHUTDOWN ; 
 int /*<<< orphan*/  CMCSR ; 
 int FLAG_CLOCKEVENT ; 
 int FLAG_CLOCKSOURCE ; 
 int FLAG_IRQCONTEXT ; 
 int FLAG_REPROGRAM ; 
 int FLAG_SKIPEVENT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  sh_cmt_clock_event_program_verify (struct sh_cmt_priv*,int) ; 
 int sh_cmt_read (struct sh_cmt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_cmt_write (struct sh_cmt_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t sh_cmt_interrupt(int irq, void *dev_id)
{
	struct sh_cmt_priv *p = dev_id;

	/* clear flags */
	sh_cmt_write(p, CMCSR, sh_cmt_read(p, CMCSR) & p->clear_bits);

	/* update clock source counter to begin with if enabled
	 * the wrap flag should be cleared by the timer specific
	 * isr before we end up here.
	 */
	if (p->flags & FLAG_CLOCKSOURCE)
		p->total_cycles += p->match_value;

	if (!(p->flags & FLAG_REPROGRAM))
		p->next_match_value = p->max_match_value;

	p->flags |= FLAG_IRQCONTEXT;

	if (p->flags & FLAG_CLOCKEVENT) {
		if (!(p->flags & FLAG_SKIPEVENT)) {
			if (p->ced.mode == CLOCK_EVT_MODE_ONESHOT) {
				p->next_match_value = p->max_match_value;
				p->flags |= FLAG_REPROGRAM;
			}

			p->ced.event_handler(&p->ced);
		}
	}

	p->flags &= ~FLAG_SKIPEVENT;

	if (p->flags & FLAG_REPROGRAM) {
		p->flags &= ~FLAG_REPROGRAM;
		sh_cmt_clock_event_program_verify(p, 1);

		if (p->flags & FLAG_CLOCKEVENT)
			if ((p->ced.mode == CLOCK_EVT_MODE_SHUTDOWN)
			    || (p->match_value == p->next_match_value))
				p->flags &= ~FLAG_REPROGRAM;
	}

	p->flags &= ~FLAG_IRQCONTEXT;

	return IRQ_HANDLED;
}