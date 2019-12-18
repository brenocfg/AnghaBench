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
struct TYPE_3__ {scalar_t__ env_phase; void* env_counter; void* env_target; int /*<<< orphan*/  env_step_r; int /*<<< orphan*/  env_step; } ;
typedef  TYPE_1__ SlotState ;

/* Variables and functions */
 scalar_t__ SCSP_ENV_ATTACK ; 
 void* SCSP_ENV_DECAY_END ; 
 scalar_t__ SCSP_ENV_RELEASE ; 

__attribute__((used)) static void ScspKeyOff(SlotState *slot)
{
   if (slot->env_phase == SCSP_ENV_RELEASE)
      return;  // Can't release a sound that's already released

   // If we still are in attack phase at release time, convert attack to decay
   if (slot->env_phase == SCSP_ENV_ATTACK)
      slot->env_counter = SCSP_ENV_DECAY_END - slot->env_counter;

   slot->env_phase = SCSP_ENV_RELEASE;
   slot->env_step = slot->env_step_r;
   slot->env_target = SCSP_ENV_DECAY_END;
}