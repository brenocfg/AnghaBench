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
struct timer_rand_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ENT (char*,int) ; 
 int /*<<< orphan*/  add_timer_randomness (struct timer_rand_state*,int) ; 
 struct timer_rand_state* get_timer_rand_state (int) ; 

void add_interrupt_randomness(int irq)
{
	struct timer_rand_state *state;

	state = get_timer_rand_state(irq);

	if (state == NULL)
		return;

	DEBUG_ENT("irq event %d\n", irq);
	add_timer_randomness(state, 0x100 + irq);
}