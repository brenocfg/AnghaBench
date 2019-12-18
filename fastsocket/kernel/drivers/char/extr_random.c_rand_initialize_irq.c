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
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct timer_rand_state* get_timer_rand_state (int) ; 
 struct timer_rand_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_timer_rand_state (int,struct timer_rand_state*) ; 

void rand_initialize_irq(int irq)
{
	struct timer_rand_state *state;

	state = get_timer_rand_state(irq);

	if (state)
		return;

	/*
	 * If kzalloc returns null, we just won't use that entropy
	 * source.
	 */
	state = kzalloc(sizeof(struct timer_rand_state), GFP_KERNEL);
	if (state)
		set_timer_rand_state(irq, state);
}