#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct TYPE_5__ {scalar_t__ envelope; int attenuation; scalar_t__ envelope_steps_taken; scalar_t__ sample_offset; scalar_t__ step_count; scalar_t__ sample_counter; } ;
struct Slot {TYPE_1__ regs; TYPE_2__ state; } ;
struct TYPE_6__ {scalar_t__ debug_mode; } ;

/* Variables and functions */
 scalar_t__ ATTACK ; 
 scalar_t__ RELEASE ; 
 TYPE_3__ new_scsp ; 
 int /*<<< orphan*/  scsp_debug_add_instrument (int /*<<< orphan*/ ) ; 

void keyon(struct Slot * slot)
{
   if (slot->state.envelope == RELEASE)
   {
      slot->state.envelope = ATTACK;
      slot->state.attenuation = 0x280;
      slot->state.sample_counter = 0;
      slot->state.step_count = 0;
      slot->state.sample_offset = 0;
      slot->state.envelope_steps_taken = 0;

      if (new_scsp.debug_mode)
         scsp_debug_add_instrument(slot->regs.sa);
   }
   //otherwise ignore
}