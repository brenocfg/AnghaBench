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
struct lguest_ro_state {int /*<<< orphan*/ * guest_idt; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_idt_entry (int /*<<< orphan*/ *,unsigned int,unsigned long const,int /*<<< orphan*/ *) ; 

void setup_default_idt_entries(struct lguest_ro_state *state,
			       const unsigned long *def)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(state->guest_idt); i++)
		default_idt_entry(&state->guest_idt[i], i, def[i], NULL);
}