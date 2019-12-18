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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int num; int /*<<< orphan*/  lfo_counter; int /*<<< orphan*/  sample_counter; int /*<<< orphan*/  output; } ;
struct Slot {TYPE_1__ state; } ;
struct Scsp {int /*<<< orphan*/ * sound_stack; } ;

/* Variables and functions */

void op7(struct Slot * slot, struct Scsp*s)
{
   u32 previous = s->sound_stack[slot->state.num + 32];
   s->sound_stack[slot->state.num + 32] = slot->state.output;
   s->sound_stack[slot->state.num] = previous;

   slot->state.sample_counter++;
   slot->state.lfo_counter++;
}