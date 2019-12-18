#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ s32 ;
struct TYPE_3__ {int sr; int octave_shift; int krs_shift; int dr; int ar; int rr; scalar_t__ env_step_r; scalar_t__ env_step_a; scalar_t__ env_step_d; scalar_t__ env_step_s; } ;
typedef  TYPE_1__ SlotState ;

/* Variables and functions */
 scalar_t__* scsp_attack_rate ; 
 scalar_t__* scsp_decay_rate ; 

__attribute__((used)) static void ScspUpdateSlotEnv(SlotState *slot)
{
   if (slot->sr)
   {
      const s32 *rate_table = &scsp_decay_rate[slot->sr << 1];
      slot->env_step_s = rate_table[(15 - slot->octave_shift)
                                    >> slot->krs_shift];
   }
   else
      slot->env_step_s = 0;

   if (slot->dr)
   {
      const s32 *rate_table = &scsp_decay_rate[slot->dr << 1];
      slot->env_step_d = rate_table[(15 - slot->octave_shift)
                                    >> slot->krs_shift];
   }
   else
      slot->env_step_d = 0;

   if (slot->ar)
   {
      const s32 *rate_table = &scsp_attack_rate[slot->ar << 1];
      slot->env_step_a = rate_table[(15 - slot->octave_shift)
                                    >> slot->krs_shift];
   }
   else
      slot->env_step_a = 0;

   if (slot->rr)
   {
      const s32 *rate_table = &scsp_decay_rate[slot->rr << 1];
      slot->env_step_r = rate_table[(15 - slot->octave_shift)
                                    >> slot->krs_shift];
   }
   else
      slot->env_step_r = 0;
}