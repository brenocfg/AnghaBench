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
struct ircomm_tty_cb {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  IRCOMM_TTY_STATE ;

/* Variables and functions */

__attribute__((used)) static inline void ircomm_tty_next_state(struct ircomm_tty_cb *self, IRCOMM_TTY_STATE state)
{
	/*
	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == IRCOMM_TTY_MAGIC, return;);

	IRDA_DEBUG(2, "%s: next state=%s, service type=%d\n", __func__ ,
		   ircomm_tty_state[self->state], self->service_type);
	*/
	self->state = state;
}