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
 struct timer_rand_state** irq_timer_state ; 

__attribute__((used)) static void set_timer_rand_state(unsigned int irq,
				 struct timer_rand_state *state)
{
	irq_timer_state[irq] = state;
}