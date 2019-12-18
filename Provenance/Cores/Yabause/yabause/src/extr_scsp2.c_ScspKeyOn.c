#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ env_phase; int /*<<< orphan*/  env_target; int /*<<< orphan*/  env_step_a; int /*<<< orphan*/  env_step; int /*<<< orphan*/  env_counter; scalar_t__ addr_counter; } ;
typedef  TYPE_1__ SlotState ;

/* Variables and functions */
 scalar_t__ SCSP_ENV_ATTACK ; 
 int /*<<< orphan*/  SCSP_ENV_ATTACK_END ; 
 int /*<<< orphan*/  SCSP_ENV_ATTACK_START ; 
 scalar_t__ SCSP_ENV_RELEASE ; 
 int /*<<< orphan*/  ScspUpdateSlotAddress (TYPE_1__*) ; 

__attribute__((used)) static void ScspKeyOn(SlotState *slot)
{
   if (slot->env_phase != SCSP_ENV_RELEASE)
      return;  // Can't key a sound that's already playing

   ScspUpdateSlotAddress(slot);

   slot->addr_counter = 0;
   slot->env_phase = SCSP_ENV_ATTACK;
   slot->env_counter = SCSP_ENV_ATTACK_START;  // FIXME: should this start at the current value if the old sound is still decaying?
   slot->env_step = slot->env_step_a;
   slot->env_target = SCSP_ENV_ATTACK_END;
}