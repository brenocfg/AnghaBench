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
struct TYPE_2__ {int envelope_steps_taken; int attenuation; int /*<<< orphan*/  sample_counter; } ;
struct Slot {TYPE_1__ state; } ;

/* Variables and functions */
 int** decay_rate_table ; 
 int get_rate (struct Slot*,int) ; 
 scalar_t__ need_envelope_step (int,int /*<<< orphan*/ ,struct Slot*) ; 

void do_decay(struct Slot * slot, int rate_in)
{
   int rate = get_rate(slot, rate_in);
   int sample_mod_4 = slot->state.envelope_steps_taken & 3;
   int decay_rate;

   if (rate <= 0x30)
      decay_rate = decay_rate_table[0][sample_mod_4];
   else
      decay_rate = decay_rate_table[rate - 0x30][sample_mod_4];

   if (need_envelope_step(rate, slot->state.sample_counter, slot))
   {
      if (slot->state.attenuation < 0x3bf)
         slot->state.attenuation += decay_rate;
   }
}