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
typedef  int u32 ;
struct TYPE_2__ {size_t step_count; int /*<<< orphan*/  envelope_steps_taken; } ;
struct Slot {TYPE_1__ state; } ;

/* Variables and functions */
 int EFFECTIVE_RATE_END ; 
 int** envelope_table ; 

int need_envelope_step(int effective_rate, u32 sample_counter, struct Slot* slot)
{
   if (sample_counter == 0)
      return 0;

   if (effective_rate == 0 || effective_rate == 1)
   {
      return 0;//never step
   }
   else if (effective_rate >= 0x30)
   {
      if ((sample_counter & 1) == 0)
      {
         slot->state.envelope_steps_taken++;
         return 1;
      }
      else
         return 0;
   }
   else
   {
      int pos = effective_rate - 2;

      int result = 0;

      int value = envelope_table[pos][slot->state.step_count];

      if (sample_counter % value == 0)
      {
         result = 1;

         slot->state.envelope_steps_taken++;
         slot->state.step_count++;

         if (envelope_table[pos][slot->state.step_count] == EFFECTIVE_RATE_END)
            slot->state.step_count = 0;//reached the end of the array
      }

      return result;
   }
   return 0;
}